void eff_sjet_new(){
    
    //gStyle->SetPadGridX(1);// グリッドの縦線を表示する（０を入れると非表示）
    //gStyle->SetPadGridY(1);// グリッドの横線を表示する（０を入れると非表示）
    
    
    cout << "-----ROC plot-----" << endl;
    TCanvas* c1 = new TCanvas("c1","c1",50,50,640,490);
    c1->SetLeftMargin(0.13);
    c1->SetTickx(1);
    c1->SetTicky(1);
    //c1->SetLogy();
    
    double pt_eff[15];
    double pt_bin[15];
    
    TGraph* flat_gr_pt = new TGraph(15, pt_bin, pt_eff);
    flat_gr_pt->SetTitle(0);
    flat_gr_pt->GetXaxis()->SetTitle("p_{T}[GeV]");
    flat_gr_pt->GetYaxis()->SetTitle("Gluon Jet Rejection Rate");
    flat_gr_pt->GetYaxis()->SetRangeUser(0, 0.91);
    flat_gr_pt->GetXaxis()->SetRangeUser(0,5000);
    flat_gr_pt->SetMarkerColor(kRed);
    flat_gr_pt->SetLineColor(kRed);
    flat_gr_pt->SetLineWidth(2);
    flat_gr_pt->SetMarkerStyle(8);
    flat_gr_pt->Draw("ALP");
    
    TLatex latex_eta;
    latex_eta.SetTextSize(0.038);
    latex_eta.SetTextAlign(13);  //align at top
    latex_eta.DrawLatex(0.80, 0.88,"#it{ATLAS} #bf{Simulation Work in progress}");
    latex_pt.DrawLatex(0.80, 0.85,"#bf{Gluon Rejection Rate @80% Quark Efficiency Rate}");
    latex_eta.SetTextSize(0.03);
    latex_eta.DrawLatex(0.80, 0.82,"#bf{#sqrt{s} = 13 TeV}");
    latex_eta.DrawLatex(0.80, 0.795,"#bf{Small-R Jet (Anti-k_{t} R=0.4)}");
    latex_eta.DrawLatex(0.80, 0.770,"#bf{p_{T}>25 GeV}");
    
    TLegend* leg1 = new TLegend(0.15,0.15,0.50,0.35);
    leg1->SetTextSize(0.045);
    leg1->SetBorderSize(0);
    leg1->SetFillStyle(0);
    leg1->AddEntry(flat_gr_eta,"Deep Sets Tagger");
    leg1->Draw("same");
    
    c1->SaveAs("conv1d_eta_eff.eps");
    
    
}
