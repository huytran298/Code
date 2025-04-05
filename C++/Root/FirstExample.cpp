#include <TCanvas.h>
#include <TH1F.h>
#include <TRandom.h>

int main() {
    // Create a histogram
    TH1F *h = new TH1F("h1", "Example Histogram", 100, -4, 4);

    // Fill the histogram with random numbers from a normal distribution
    for (int i = 0; i < 10000; ++i) {
        h->Fill(gRandom->Gaus(0, 1));
    }

    // Create a canvas to draw the histogram
    TCanvas *c1 = new TCanvas("c1", "Canvas", 800, 600);
    h->Draw();

    // Wait for user to close the window
    c1->Update();
    c1->WaitPrimitive();

    return 0;
}
