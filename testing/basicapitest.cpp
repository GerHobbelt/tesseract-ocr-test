#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

#include "monolithic_tests.h"

#include <stdio.h>


static bool fileExists(const char *path) {
	FILE *f = fopen(path, "rb");
	if (!f)
		return false;
	fclose(f);
	return true;
}


#if defined(BUILD_MONOLITHIC)
#  define main tesseract_basicAPI_test_main
#  define TESTFILE_PATHPREFIX  "../../thirdparty/tesseract/test/"
#else
#  define TESTFILE_PATHPREFIX  ""
#endif

int main(int argc, const char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Missing testfilepath argument.\n");
		return 1;
	}
	
	const char *testfilepath = argv[1];
	if (!testfilepath || !*testfilepath) {
		testfilepath = TESTFILE_PATHPREFIX "../test/testing/phototest.tif";
	}
	if (!fileExists(testfilepath)) {
		fprintf(stderr, "Could not access test file \"%s\".\n", testfilepath);
		return 1;
	}

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English
    if (api->InitSimple("../../tessdata", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        return 1;
    }

    // Open input image with leptonica library
    Pix *image = pixRead(testfilepath);
    api->SetImage(image);
    // Get OCR result
    char *outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
	delete [] outText;
	pixDestroy(&image);
	api->End();
    delete api;

	tesseract::TessBaseAPI::ClearPersistentCache();

    return 0;
}
