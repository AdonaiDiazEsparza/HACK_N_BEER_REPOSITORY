// ExecHackAndBeer.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <Windows.h>


#ifdef _WIN64

#define MODULE_PATH L"HackAndBeer.dll"

#else

#define MODULE_PATH L"HackAndBeer.dll"

#endif

// === Logs =======================

#define LOG_OK(fmt, ...)\
	printf("[+] " fmt "\n", ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...)\
	printf("[-] " fmt "\n", ##__VA_ARGS__)

#define LOG_INFO(fmt, ...)\
	printf("[!] " fmt "\n", ##__VA_ARGS__)

// ================================

typedef int (*suma)(int, int);

suma FuncSum = NULL;

HINSTANCE hInstLibrary = NULL;


BOOL configModule()
{
	hInstLibrary = LoadLibrary(MODULE_PATH);

	if (!hInstLibrary)
	{
		LOG_ERROR("Modulo no cargado. E: %d", GetLastError());
		return FALSE;
	}

	FuncSum = (suma) GetProcAddress(hInstLibrary, "suma");

	if (!FuncSum)
	{
		LOG_ERROR("Funcion Suma no obtenida");
		return FALSE;
	}

	return TRUE;
}


int main(int argc, const char* argv[])
{
	if (argc < 3) {
		LOG_ERROR("Faltan Parametros\n");
		return 0;
	}

	if (argc > 3) {
		printf("Demasiados Parametros\n");
		return 0;
	}

	if (configModule())
	{

		int numero_a = atoi(argv[1]);
		int numero_b = atoi(argv[2]);

		int resultado = FuncSum(numero_a, numero_b);

		LOG_INFO("El resultado de suma %d y %d es igual a %d", numero_a, numero_b, resultado);
    }

	if (hInstLibrary)
	{
		FreeLibrary(hInstLibrary);
	}
}