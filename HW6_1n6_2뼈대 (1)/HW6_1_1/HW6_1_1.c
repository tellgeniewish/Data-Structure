//
void write_graph(GraphType *g, char *filename)
{
     int i, j;
     FILE *fp;
     
     if (filename == NULL) fp = stdout;
     else {
          fp = fopen(filename, "wt");
	     if (fp == NULL) 
	     {
		     printf("file %s open error!\n", filename);
	          return;
	     }
     }

     // ÄÚµå »ðÀÔ

     if (filename != NULL) fclose(fp);
}



     
	