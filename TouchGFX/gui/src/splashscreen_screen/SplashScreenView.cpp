#include <gui/splashscreen_screen/SplashScreenView.hpp>

SplashScreenView::SplashScreenView()
{

}

void SplashScreenView::setupScreen()
{
    SplashScreenViewBase::setupScreen();
    HAL::getInstance()->setFrameRateCompensation(true);

    //This function enables/disable Chrom-ART, the DMA2D hardware accelerator
  HAL::getInstance()->enableDMAAcceleration(true);

}

void SplashScreenView::tearDownScreen()
{
    SplashScreenViewBase::tearDownScreen();
    HAL::getInstance()->enableDMAAcceleration(true);
}
