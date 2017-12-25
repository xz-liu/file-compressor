
#pragma warning(disable:4996)

extern int rb_main();
extern int zip_main(int argc, char** argv);

int main(int argc,char ** argv) {
	if (argc < 3)rb_main();
	else { zip_main(argc,argv); }
	return 0;
}


