#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>


static int sqlite_callback(void *arg, int argc, char **argv, char **col_name) {
	bool *columns_printed = (bool*)arg;

	if (!(*columns_printed)) {
		for (int i = 0; i < argc; ++i) {
			printf("%s", col_name[i]);
			if (i < argc-1) printf(" | ");
			else printf("\n");
		}
		printf("---------------\n");
		*columns_printed = true;
	}

	for (int i = 0; i < argc; ++i) {
		printf("%s", argv[i]);
		if (i < argc-1) printf(" | ");
		else printf("\n");
	}

	return 0;
}

int main(int argc, char** argv) {

	if (argc < 3) {
		fprintf(stderr, "[ERROR] Insufficient Arguments!\n");
		fprintf(stderr, "Usage: %s <database> <sql-statement>\n", argv[0]);
		return 1;
	}

	const char *filename = argv[1];
	sqlite3* db = NULL;

	if (sqlite3_open(filename, &db)) {
		fprintf(stderr, "[ERROR] Couldn't open database '%s': %s", filename, sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	printf("[INFO] Opened database '%s'\n", filename);

	char* err_msg = NULL;
	bool columns_printed = false;
	if (sqlite3_exec(db, argv[2], sqlite_callback, &columns_printed, &err_msg) != SQLITE_OK) {
		fprintf(stderr, "[ERROR] Failed to exec '%s': %s", argv[2], err_msg);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_close(db);
	return 0;
}
