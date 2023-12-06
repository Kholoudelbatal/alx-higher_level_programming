#include <Python.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);

/**
 * print_python_list - print info Python lists.
 * @p: A PyObject list object.
 */
void print_python_list(PyObject *p)
{
	int s, alloc, ind;
	const char *type;
	PyListObject *list = (PyListObject *)p;
	PyVarObject *var = (PyVarObject *)p;

	s = var->ob_s;
	alloc = list->allocated;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %d\n", s);
	printf("[*] Allocated = %d\n", alloc);

	for (ind = 0; ind < s; ind++)
	{
		type = list->ob_item[ind]->ob_type->tp_name;
		printf("Element %d: %s\n", ind, type);
		if (strcmp(type, "bytes") == 0)
			print_python_bytes(list->ob_item[ind]);
	}
}

/**
 * print_python_bytes - print python byte objects.
 * @p: A PyObject byte object
 */
void print_python_bytes(PyObject *p)
{
	unsigned char ind, s;
	PyBytesObject *bytes = (PyBytesObject *)p;

	printf("[.] bytes object info\n");
	if (strcmp(p->ob_type->tp_name, "bytes") != 0)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	printf("  size: %ld\n", ((PyVarObject *)p)->ob_s);
	printf("  trying string: %s\n", bytes->ob_sval);

	if (((PyVarObject *)p)->ob_s > 10)
		s = 10;
	else
		s = ((PyVarObject *)p)->ob_s + 1;

	printf("  first %d bytes: ", s);
	for (ind = 0; ind < s; ind++)
	{
		printf("%02hhx", bytes->ob_sval[ind]);
		if (ind == (s - 1))
			printf("\n");
		else
			printf(" ");
	}
}
