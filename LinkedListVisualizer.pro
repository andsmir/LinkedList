TEMPLATE = subdirs
SUBDIRS = ll_library test LLgui
test.depends = ll_library
LLgui.depends = ll_library
