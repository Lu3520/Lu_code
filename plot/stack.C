void minmass_mass(){
  
  gStyle->SetOptStat(0);
  gStyle->SetTitleAlign(33);
  gStyle->SetTitleX(.99);
  
  THStack *hs_jet_pt = new THStack("hs_jet_pt","hs_jet_pt");
  //hs_jet_pt->SetMaximum(1700000);

  TFile* VBS_data = new TFile("../signal/output/2leading/VBS.root");
  TFile* lep_data = new TFile("../bkg/output/2leading/lep.root");
  TFile* ttbar_data = new TFile("../ttbar_nonallhad_bkg/output/2leading/ttbar.root");
  
  //TH1D *h1_VBS = (TH1D*)VBS_data->Get("h1_mWboson_2leading");
  TH1D *h1_VBS = (TH1D*)VBS_data->Get("h1_mWboson_minmass");
  //TH1D *h1_VBS = (TH1D*)VBS_data->Get("h1_mtag");
  h1_VBS->Rebin(15);
  h1_VBS->SetFillColor(2);
  h1_VBS->SetLineWidth(0);
  h1_VBS->SetMarkerColor(2);
  //TH1D *h1_lep = (TH1D*)lep_data->Get("h1_mWboson_2leading");
  TH1D *h1_lep = (TH1D*)lep_data->Get("h1_mWboson_minmass");
  //TH1D *h1_lep = (TH1D*)lep_data->Get("h1_mtag");
  h1_lep->Rebin(15);
  h1_lep->SetFillColor(9);
  h1_lep->SetLineWidth(0);
  h1_lep->SetMarkerColor(9);
  //TH1D *h1_ttbar = (TH1D*)ttbar_data->Get("h1_mWboson_2leading");
  TH1D *h1_ttbar = (TH1D*)ttbar_data->Get("h1_mWboson_minmass");
  //TH1D *h1_ttbar = (TH1D*)ttbar_data->Get("h1_mtag");
  h1_ttbar->Rebin(15);
  h1_ttbar->SetFillColor(8);
  h1_ttbar->SetLineWidth(0);
  h1_ttbar->SetMarkerColor(8);
  //h1_ttbar->GetYaxis()->SetRangeUser(0, 0.02);
  //h1_VBS->GetXaxis()->SetRangeUser(0,3000);
  //h1_lep->GetXaxis()->SetRangeUser(0,3000);
  //h1_ttbar->GetXaxis()->SetRangeUser(0,3000);
  
  h1_VBS->Scale(139000000);
  h1_lep->Scale(139000000);
  h1_ttbar->Scale(139000000);
  h1_VBS->Scale(100);
  hs_jet_pt->Add(h1_ttbar);
  hs_jet_pt->Add(h1_lep);
  hs_jet_pt->Add(h1_VBS);
 
  TH1D* h1_significance = new TH1D("h1_significance", "h1_significance", 400, 1, 6000);
  h1_significance->SetTitle(0);
  h1_significance->SetLineColor(kRed);
  h1_significance->GetXaxis()->SetTitle("m_{jj}[GeV]");
  h1_significance->GetYaxis()->SetTitle("significance");
  //h1_significance->SetYTitle("significance");
  for(int i=1; i<61; i++){
    double sig_num = h1_VBS->GetBinContent(i);
    double bkg_num = h1_ttbar->GetBinContent(i) + h1_lep->GetBinContent(i);
    double significance = 0;
    if(bkg_num!=0){
      significance = sig_num/std::sqrt(bkg_num + bkg_num*bkg_num*0.1*0.1);
    }
    if(bkg_num==0) significance = 0;
    h1_significance->SetBinContent(i, significance);
  }
  /*TCanvas* c1 = new TCanvas("c1","c1",50,50,640,490);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetLeftMargin(0.13);
  c1->SetLogy();
  hs_jet_pt->Draw("hist");
  hs_jet_pt->GetXaxis()->SetRangeUser(1, 4000);
  //hs_jet_pt->GetYaxis()->SetRangeUser(0, 0.02);
  hs_jet_pt->GetXaxis()->SetTitle("m^{tag}_{jj}");
  hs_jet_pt->GetYaxis()->SetTitle("Event/20GeV");*/

  /*TLatex latex_a;
  latex_a.SetTextSize(0.038);
  latex_a.SetTextAlign(13);  //align at top
  latex_a.DrawLatex(1000, 2000000,"#it{ATLAS} #bf{Simulation Work in progress}");
  latex_a.SetTextSize(0.03);
  latex_a.DrawLatex(1000, 1500000,"#bf{#sqrt{s} = 13 TeV}, 139 fb^{-1}");*/


  TCanvas *c1 = new TCanvas("c1", "the canvas",50,50,600,600);
  gStyle->SetOptStat(0);
  c1->SetTopMargin(0.13);
  //c1->SetLeftMargin(0.13);
  c1->SetTickx(1);
  c1->SetTicky(1);

  TPad* pad1 = new TPad("pad1","The pad with the function", 0.05,0.30,0.95,0.95,0);
  pad1->SetTopMargin(0.01);
  pad1->SetBottomMargin(0.02);
  pad1->SetLeftMargin(0.14); //make yasis left
  pad1->SetTickx(1);
  pad1->SetTicky(1);
  //pad1->SetLogy();
  TPad* pad2 = new TPad("pad2","The pad with the histogram", 0.05,0.03,0.95,0.30,0);
  pad2->SetBottomMargin(0.15);
  pad2->SetTopMargin(0.02);
  pad2->SetLeftMargin(0.14); //make yasis left
  pad2->SetBottomMargin(0.2);
  pad2->SetTickx(1);
  pad2->SetTicky(1);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  hs_jet_pt->Draw("hist");
  hs_jet_pt->GetXaxis()->SetRangeUser(1, 500);
  hs_jet_pt->GetXaxis()->SetTitle(0);
  hs_jet_pt->GetXaxis()->SetLabelSize(0);
  hs_jet_pt->GetYaxis()->SetLabelSize(0.035);
  hs_jet_pt->GetYaxis()->SetTitleSize(0.04);
  hs_jet_pt->GetYaxis()->SetTitleSize(0.04);
  //hs_plot->GetYaxis()->SetTitle("#frac{signal}{#sqrt{bkg}}");
  hs_jet_pt->GetYaxis()->SetTitle("Event/15GeV");
  hs_jet_pt->GetXaxis()->SetTitle(0);
  hs_jet_pt->SetTitle(0);
  //hs_jet_pt->GetXaxis()->SetRangeUser(64, 106);
  //hs_jet_pt->Draw("hist");
  
  TLegend* leg = new TLegend(0.50,0.50,0.70,0.70);
  leg->SetTextSize(0.035);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h1_VBS, "VBS Sample x 100");
  leg->AddEntry(h1_lep, "W+jet Sample");
  leg->AddEntry(h1_ttbar, "t#bar{t} Sample");
  leg->AddEntry((TObject*)0,"minmass","");
  leg->Draw("same");

  TLatex latex_a;
  latex_a.SetTextSize(0.038);
  latex_a.SetTextAlign(13);  //align at top
  latex_a.DrawLatex(225, 395000,"#it{ATLAS} #bf{Simulation Work in progress}");
  latex_a.SetTextSize(0.03);
  latex_a.DrawLatex(225, 380000,"#bf{#sqrt{s} = 13 TeV}, 139 fb^{-1}");

  pad2->cd();
  //pad2->SetLeftMargin(0.03);
  h1_significance->GetXaxis()->SetRangeUser(1, 500);
  h1_significance->GetYaxis()->SetLabelSize(0.08);
  h1_significance->GetYaxis()->SetTitleSize(0.08);
  h1_significance->GetXaxis()->SetLabelSize(0.08);
  h1_significance->GetXaxis()->SetTitleSize(0.08);
  h1_significance->Draw("hist");


  /*TCanvas* c2 = new TCanvas("c2","c2",50,50,640,490);
  c2->SetLeftMargin(0.13);
  //c2->SetLogy();
  TH1D* h1_allfile = new TH1D(*h1_ttbar + *h1_lep + *h1_VBS);
  //TH1D* h1_allfile = new TH1D(*h1_VBS);
  //h1_allfile->Rebin(100);
  h1_allfile->SetTitle("mWboson");
  //h1_allfile->GetXaxis()->SetRangeUser(1,150);
  h1_allfile->GetXaxis()->SetTitle("m_{2nd Small-R Jet}[GeV]");
  h1_allfile->GetYaxis()->SetTitle("Event/20GeV");
  h1_allfile->SetMarkerStyle(4);
  h1_allfile->SetMarkerColor(kBlue);
  h1_allfile->SetLineColor(kBlue);
  h1_allfile->Draw();*/


  /*TCanvas* c3 = new TCanvas("c3", "c3", 50, 50, 640, 490);
  c3->SetLeftMargin(0.13);
  TH2D* h2_VBS = (TH2D*)VBS_data->Get("h2_mtag_detatag");
  TH2D* h2_lep = (TH2D*)lep_data->Get("h2_mtag_detatag");
  TH2D* h2_ttbar = (TH2D*)ttbar_data->Get("h2_mtag_detatag");

  h2_VBS->Add(h2_lep);
  h2_VBS->Add(h2_ttbar);
  h2_VBS->SetTitle(0);
  h2_VBS->GetXaxis()->SetTitle("M_{tag}[GeV]");
  h2_VBS->GetYaxis()->SetTitle("#Delta#eta_{tag}");
  h2_VBS->Draw();*/

}
