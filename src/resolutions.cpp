#include "resolutions.h"

resHandler::resHandler(int w, int h, float resMod, float targWldx, float targWldy) {
    this->w = w * resMod;
    this->h = h * resMod;
    this->resMod = resMod;
    this->wldToScrx = targWldx * resMod;
    this->wldToScry = targWldy * resMod;
}