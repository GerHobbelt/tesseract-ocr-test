#include <allheaders.h>
#include <stdio.h>
#include <tesseract/baseapi.h>



#if defined(BUILD_MONOLITHIC)
#  define main tesseract_basicAPI_test_main
#endif

int main(void) {
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English
    if (api->InitSimple("../../tessdata", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix *image = pixRead("../test/testing/phototest.tif");
    api->SetImage(image);
    // Get OCR result
    char *outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete api;
    delete [] outText;
    pixDestroy(&image);

    return 0;
}
