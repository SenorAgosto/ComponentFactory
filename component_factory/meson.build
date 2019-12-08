comp_factory_src = [
]
component_factory_lib = static_library('component_factory', comp_factory_src, include_directories : [includes])
component_factory = declare_dependency(link_with : component_factory_lib, include_directories : [includes])

comp_factory_test_src = [
	'component_factory-ut.cpp',
	'details/search_tuple-ut.cpp',
]
comp_factory_test = executable('component_factory_ut', [comp_factory_test_src, ut_main], dependencies : [component_factory, unittest_cpp])
test('component factory tests', comp_factory_test)
