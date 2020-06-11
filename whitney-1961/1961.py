import bpy
import math
import re
from collections import namedtuple

Vector = namedtuple('Vector', ['x', 'y', 'z'])

def save(name):
  bpy.context.scene.render.image_settings.file_format='PNG'
  bpy.context.scene.render.filepath = 'out/' + name
  bpy.ops.render.render(write_still=True)

def deselectAll():
  for obj in bpy.data.objects:
    obj.select_set(False)

def printObjects():
  for obj in bpy.data.objects:
    print(obj.name)

def setupBlender():
  deselectAll()
  bpy.data.objects['Camera'].select_set(True)
  bpy.data.objects['Cube'].select_set(True)
  bpy.data.objects['Light'].select_set(True)
  bpy.ops.object.delete()
  bpy.context.scene.render.engine = 'CYCLES'
  bpy.context.scene.cycles.device = 'GPU'
  bpy.context.scene.cycles.samples = 4
  bpy.context.scene.cycles.film_exposure = 2.5

def insert(text, letter, at):
  content = text.data.body
  text.data.body = content[:at] + letter + content[at:]

def splice(text, start, amt):
  content = text.data.body
  text.data.body = content[:start] + content[start+amt:]

def addText(text):
  bpy.ops.object.text_add(enter_editmode=False, align='WORLD', location=(0,0,0))
  textObjects = getTextObjects()
  splice(textObjects[-1], 0, 4)
  x = 0
  for c in text:
    insert(textObjects[-1], c, x)
    x += 1

  return textObjects[-1]

def getTextObjects():
  textObjects = []
  for obj in bpy.data.objects:
    if (re.match("Text", obj.name)):
      # print(obj.name)
      textObjects.append(obj)
  return textObjects

def lookat(location, camera):

  xIn = camera.location.x - location.x
  yIn = camera.location.y - location.y
  zIn = camera.location.z - location.z

  x = math.pi / 2
  y = 0
  z = 0

  try:
    z = math.atan(yIn/xIn)
  except ZeroDivisionError:
    print('div error')
    z = 0

  if xIn >= 0:
    z += math.pi / 2
  else:
    z -= math.pi / 2

  try:
    x = math.atan(math.sqrt(yIn * yIn + xIn * xIn) / zIn)
  except ZeroDivisionError:
    print('div error 2')
    x = 0

  if zIn < 0:
    x += math.pi
  elif zIn == 0:
    x += math.pi / 2

  camera.rotation_euler = (x, y, z)

def getCameras():
  cameras = []
  for obj in bpy.data.objects:
    if (re.match("Camera", obj.name)):
      # print(obj.name)
      cameras.append(obj)
  return cameras

def getMaterials():
  mats = []
  for obj in bpy.data.materials:
    if (re.match("Material", obj.name)):
      # print(obj.name)
      mats.append(obj)
  return mats

def backgroundMat(mat):
  mat.node_tree.nodes["Principled BSDF"].inputs[0].default_value = (0, 0, 0, 1) # base color
  mat.node_tree.nodes["Principled BSDF"].inputs[7].default_value = 0.3 # roughness

def textMat(mat):
  principled = mat.node_tree.nodes["Principled BSDF"]
  texCoord = mat.node_tree.nodes.new('ShaderNodeTexCoord')
  vecRotate = mat.node_tree.nodes.new('ShaderNodeVectorRotate')
  colorRamp = mat.node_tree.nodes.new('ShaderNodeValToRGB')

  links = mat.node_tree.links

  links.new(texCoord.outputs['Generated'], vecRotate.inputs['Vector'])
  links.new(vecRotate.outputs['Vector'], colorRamp.inputs['Fac'])
  links.new(colorRamp.outputs['Color'], principled.inputs['Base Color'])
  links.new(colorRamp.outputs['Color'], principled.inputs['Emission'])

  vecRotate.inputs[3].default_value = math.pi / 4

  colorRamp.color_ramp.elements[0].color = (0, 1, 0.1, 1)
  colorRamp.color_ramp.elements[1].color = (0, 0.2, 1, 1)

  colorRamp.color_ramp.elements[0].position = 0.315
  colorRamp.color_ramp.elements[1].position = 0.705


def map(val, start1, stop1, start2, stop2):
  return (val - start1) / (stop1 - start1) * (stop2 - start2) + start2

def saveHelp(frame, length):
  k = str(frame)
  while len(k) < length:
    k = '0' + k
  return k

def setup():

  setupBlender()

  bpy.ops.mesh.primitive_plane_add(size=5, enter_editmode=False, align="WORLD", location=(0, 0, -0.3))

  bpy.ops.object.camera_add(location=(0, 0, 6))
  bpy.context.scene.camera = bpy.data.objects['Camera']

  bpy.ops.material.new()
  bpy.ops.material.new()
  mats = getMaterials()

  # background mat
  backgroundMat(mats[1])

  plane = bpy.context.scene.objects['Plane']
  plane.data.materials.append(mats[1])
  plane.material_slots[0].material = mats[1]


  # text mat
  textMat(mats[2])

  # create text
  txts = []

  for i in range(16):
    txt = addText('1961')
    txts.append(txt)

  for i in range(len(txts)):
  # txt = addText('1961')
    txts[i].data.extrude = 0.1
    txts[i].data.align_x = 'CENTER'
    txts[i].data.align_y = 'CENTER'

    txts[i].data.materials.append(mats[2])
    txts[i].material_slots[0].material = mats[2]

  frames = 240
  for r in range(0, frames):
    for i in range(len(txts)):
      angle = map(i, 0, len(txts), 0, 2 * math.pi)
      radius = map(r, 0, frames, 0, 2)
      txts[i].location[0] = radius * math.cos(angle)
      txts[i].location[1] = radius * math.sin(angle)
    save('1961-' + saveHelp(r, 3))


setup()