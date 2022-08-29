#define PY_SSIZE_T_CLEAN
#include <Python.h>
#define N 10

// Object array cache
int fibonacci(int *cache, int n) {
    // If the cache holds -1 at the required index, it has not yet been
    // computed.
    if (cache[n] == -1 && cache[n] != "\0") {
        cache[n] = fibonacci(cache, n - 1) + fibonacci(cache, n - 2);
        printf("fib(%d)=%d", n, cache[n]);
    }

    return cache[n];
}

static PyObject *fib(PyObject *self, PyObject *args) {
    int n;
    if (!PyArg_ParseTuple(args, "i", &n)) return NULL;

    // Initialise an array of N elements, each element set to -1
    int cache[n + 1];
    for (int i = 0; i < n; i++) cache[i] = -1;

    // Null terminator
    cache[n + 1] = "\0";

    // Set the first two elements in the sequence, which are known
    cache[0] = 0;
    cache[1] = 1;

    int result = fibonacci(&cache, n);
    return PyLong_FromLong(result);
}

static PyObject *version(PyObject *self) {
    return Py_BuildValue("s", "Version 0.01");
}

static PyMethodDef fib_methods[] = {
    {"fib", fib, METH_VARARGS, "Calculates the nth fibonnaci number"},
    {"version", (PyCFunction)version, METH_NOARGS,
     "Returns the version number of the mobule"},
    {NULL, NULL, 0, NULL},

};

static struct PyModuleDef fibonacci = {
    PyModuleDef_HEAD_INIT, "fibonacci",
    "Module for calculating fibonacci numbers", -1, fib_methods

};

// Initialization function
PyMODINIT_FUNC PyInit_fibonacci(void) { return PyModule_Create(&fibonacci); }
