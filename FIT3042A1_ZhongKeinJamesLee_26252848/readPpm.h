// global variables creator and the pre-defined color components
#define CREATOR "JAMSAWAMSA"
#define RGB_COMPONENT_COLOR 255

// reads the PPM file
static ppmImage *readPpm(const char *file)
{
         char buffer[16];
         ppmImage *img;
         FILE *fp;
         int c, rgb_comp_color;
         // open the PPM file for reading
         fp = fopen(file, "rb");
         if (!fp) {
              fprintf(stderr, "Unable to open file '%s'\n", file);
              exit(1);
         }

         // read the image format
         if (!fgets(buffer, sizeof(buffer), fp)) {
              perror(file);
              exit(1);
         }

    // checks for the correct image format
    if (buffer[0] != 'P' && (buffer[1] != '6' || buffer[1] != '3')) {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    // allocaate memory error
    img = (ppmImage *)malloc(sizeof(ppmImage));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    // check for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }

    ungetc(c, fp);
    // reads the image size information
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", file);
         exit(1);
    }

    // reads rgb component value
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", file);
         exit(1);
    }

    // checks the rgb color component
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
         fprintf(stderr, "'%s' does not have 8-bit RGB components\n", file);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    // allocates memory for pixel data
    img->data = (ppmPixel*)malloc(img->x * img->y * sizeof(ppmPixel));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    // reads pixel data from the image file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image file '%s'\n", file);
         exit(1);
    }
    fclose(fp);
    return img;
}