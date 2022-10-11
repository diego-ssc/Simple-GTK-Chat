project('proyecto1', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

add_global_arguments('-lpthread', '-rdynamic', language : 'cpp')

shared_library('proyecto1')

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')


jsondep = dependency('jsoncpp')
gtkdep = dependency('gtk+-3.0')
thread_dep = dependency('threads')

project_description = 'Primer proyecto'

src = [
       'src/main/proyecto1/Proyecto1.cc',
       'src/main/proyecto1/vista/Vista.cc',
       'src/main/proyecto1/controlador/Chat.cc',
       'src/main/proyecto1/modelo/Cliente.cc',
       'src/main/proyecto1/modelo/Servidor.cc',
       'src/main/proyecto1/modelo/Procesador.cc',
       'src/main/proyecto1/modelo/Procesador_Servidor.cc',
       'src/main/proyecto1/modelo/Procesador_Cliente.cc',
       'src/main/proyecto1/modelo/Usuario.cc',
       'src/main/proyecto1/modelo/Cuarto.cc',
       'src/main/proyecto1/vista/Vista_Cliente.cc',
       'src/main/proyecto1/vista/Vista_Servidor.cc'
]					     

tests_src = [
  'src/test/Test_Aplicacion.cc',
]  
e = executable(
  'Test_Aplicacion',
  tests_src,
  dependencies : [
    gtest_dep,
    gmock_dep]
)    
test('gtest tests', e)

exe = executable('proyecto1', src,
dependencies : [thread_dep, gtkdep, jsondep], install : true)

test('Test_Aplicacion', e)
