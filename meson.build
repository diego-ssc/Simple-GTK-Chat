project('proyecto1', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

gtkdep = dependency('gtk+-3.0')

project_description = ''

src = [
       'src/main/proyecto1/Proyecto1.cc',
       'src/main/proyecto1/vista/Vista.cc',
       'src/main/proyecto1/controlador/Chat.cc',
       'src/main/proyecto1/controlador/Controlador.cc'
]

exe = executable('proyecto1', src,
dependencies : gtkdep, install : true)

test('basic', exe)
