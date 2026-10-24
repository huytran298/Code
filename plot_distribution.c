#include <TMath.h>
#include <TF1.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <ROOT/RDataFrame.hxx>

// --- Các hàm toán học độc lập ---
Double_t myPoisson(Double_t *x, Double_t *par) {
    return par[1] * TMath::Poisson(x[0], par[0]);
}

Double_t myLorentz(Double_t *x, Double_t *par) {
    return par[0] * TMath::BreitWigner(x[0], par[1], par[2]);
}

// --- Hàm chính ---
void plot_distribution() {
    auto df = ROOT::RDF::FromCSV("data.csv");
    
    // ==========================================
    // THIẾT LẬP SỐ LƯỢNG NHÓM (BINS) TẠI ĐÂY
    int X = 76; // <--- Bạn muốn bao nhiêu nhóm thì sửa số này
    // ==========================================

    // Lấy giá trị lớn nhất và nhỏ nhất của cột Count để làm giới hạn trục X
    int min_val = *df.Min("Count");
    int max_val = *df.Max("Count");
    
    // Khởi tạo Histogram với số lượng nhóm là X
    // Trục X sẽ trải dài từ (min - 0.5) đến (max + 0.5) để bao trọn dữ liệu
    auto hist_rdf = df.Histo1D({"hist", ";so dem;tan so", X, (double)min_val - 0.5, (double)max_val + 0.5}, "Count");

    TH1D *h = (TH1D*)hist_rdf->Clone("h_fit");

    // Định dạng điểm dữ liệu
    h->SetMarkerStyle(20);       
    h->SetMarkerSize(1.0);       
    h->SetMarkerColor(kBlack);   
    h->SetLineColor(kBlack);     

    // Lấy thông số mồi cho Fit
    double mean = h->GetMean();
    double rms = h->GetRMS();
    double x_min = h->GetXaxis()->GetXmin();
    double x_max = h->GetXaxis()->GetXmax();
    
    // Tính diện tích Histogram (TỰ ĐỘNG THÍCH ỨNG VỚI SỐ LƯỢNG X BINS MỚI)
    double area = h->Integral() * h->GetBinWidth(1); 

    // Khởi tạo 3 hàm Fit
    TF1 *f_gaus = new TF1("f_gaus", "gaus", x_min, x_max);
    f_gaus->SetLineColor(kRed);
    f_gaus->SetLineWidth(2);
    f_gaus->SetLineStyle(1); 

    TF1 *f_lorentz = new TF1("f_lorentz", myLorentz, x_min, x_max, 3);
    f_lorentz->SetParameters(area, mean, rms);
    f_lorentz->SetLineColor(kBlue);
    f_lorentz->SetLineWidth(2);
    f_lorentz->SetLineStyle(2); 

    TF1 *f_poisson = new TF1("f_poisson", myPoisson, x_min, x_max, 2);
    f_poisson->SetParameters(mean, area);
    f_poisson->SetLineColor(kGreen+2);
    f_poisson->SetLineWidth(2);
    f_poisson->SetLineStyle(7); 

    // Fit
    h->Fit(f_gaus, "0 Q");
    h->Fit(f_lorentz, "0 Q");
    h->Fit(f_poisson, "0 Q");

    // Scale trục Y tự động
    double max_y = h->GetMaximum();
    if (f_gaus->GetMaximum() > max_y) max_y = f_gaus->GetMaximum();
    if (f_lorentz->GetMaximum() > max_y) max_y = f_lorentz->GetMaximum();
    if (f_poisson->GetMaximum() > max_y) max_y = f_poisson->GetMaximum();
    h->SetMaximum(max_y * 1.2);

    // Vẽ Canvas
    TCanvas *c = new TCanvas("c", "Canvas Fit", 800, 600);
    h->Draw("P"); 
    f_gaus->Draw("SAME");
    f_lorentz->Draw("SAME");
    f_poisson->Draw("SAME");

    // Hộp chú thích
    TLegend *leg = new TLegend(0.65, 0.65, 0.88, 0.88);
    leg->SetBorderSize(1);
    leg->SetFillColor(kWhite);
    leg->AddEntry(h, "Du lieu (so dem)", "p");
    leg->AddEntry(f_gaus, "Ham Gaussian", "l");
    leg->AddEntry(f_lorentz, "Ham Lorentzian", "l");
    leg->AddEntry(f_poisson, "Ham Poisson", "l");
    leg->Draw();
    
    c->Draw();
}