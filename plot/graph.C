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
    
    pt_eff[0] = 0.308;
    pt_eff[1] = 0.576;
    pt_eff[2] = 0.667;
    pt_eff[3] = 0.680;
    pt_eff[4] = 0.692;
    pt_eff[5] = 0.702;
    pt_eff[6] = 0.704;
    pt_eff[7] = 0.707;
    pt_eff[8] = 0.710;
    pt_eff[9] = 0.712;
    pt_eff[10] = 0.717;
    pt_eff[11] = 0.725;
    pt_eff[12] = 0.725;
    pt_eff[13] = 0.737;
    pt_eff[14] = 0.818;
    
    pt_bin[0] = 62.5;
    pt_bin[1] = 150;
    pt_bin[2] = 250;
    pt_bin[3] = 350;
    pt_bin[4] = 450;
    pt_bin[5] = 550;
    pt_bin[6] = 650;
    pt_bin[7] = 750;
    pt_bin[8] = 850;
    pt_bin[9] = 950;
    pt_bin[10] = 1250;
    pt_bin[11] = 1750;
    pt_bin[12] = 2500;
    pt_bin[13] = 3500;
    pt_bin[14] = 4500;
    
    
    //conv1d_flat_flat
    double flat_pt_eff[15];
    flat_pt_eff[0] = 0.3371600365813454;
    //flat_pt_eff[0] = 0.3680105318688457;
    flat_pt_eff[1] = 0.5787162930893437;
    flat_pt_eff[2] = 0.6634954707764622;
    flat_pt_eff[3] = 0.6774926096640805;
    flat_pt_eff[4] = 0.6896688996303605;
    flat_pt_eff[5] = 0.6993685663388205;
    flat_pt_eff[6] = 0.7019249916372041;
    flat_pt_eff[7] = 0.7049338685960977;
    flat_pt_eff[8] = 0.7076222674526673;
    flat_pt_eff[9] = 0.7090621068911709;
    flat_pt_eff[10] = 0.7129104357146416;
    flat_pt_eff[11] = 0.7212562579634456;
    flat_pt_eff[12] = 0.7186052197549815;
    flat_pt_eff[13] = 0.731546789291385;
    flat_pt_eff[14] = 0.7814369358615184;
    
    TGraph* flat_gr_pt = new TGraph(15, pt_bin, flat_pt_eff);
    flat_gr_pt->SetTitle(0);
    flat_gr_pt->GetXaxis()->SetTitle("p_{T}[GeV]");
    flat_gr_pt->GetYaxis()->SetTitle("Gluon Jet Rejection Rate");
    flat_gr_pt->GetYaxis()->SetRangeUser(0, 0.91);
    flat_gr_pt->GetXaxis()->SetRangeUser(0,5000);
    flat_gr_pt->SetMarkerColor(kRed);
    flat_gr_pt->SetLineColor(kRed);
    flat_gr_pt->SetLineWidth(2);
    flat_gr_pt->SetMarkerStyle(8);
    
    
    //energyflow
    double energyflow_pt_eff[15];
    energyflow_pt_eff[0] = 0.3401924726318648;
    energyflow_pt_eff[1] = 0.5727450058288399;
    energyflow_pt_eff[2] = 0.6561870465157629;
    energyflow_pt_eff[3] = 0.6711968935329229;
    energyflow_pt_eff[4] = 0.683210275907816;
    energyflow_pt_eff[5] = 0.6923572467586168;
    energyflow_pt_eff[6] = 0.6951064077825255;
    energyflow_pt_eff[7] = 0.698832849786343;
    energyflow_pt_eff[8] = 0.7017860705833607;
    energyflow_pt_eff[9] = 0.7037772468866472;
    energyflow_pt_eff[10] = 0.708586754273965;
    energyflow_pt_eff[11] = 0.7181069980161298;
    energyflow_pt_eff[12] = 0.7155566156479803;
    energyflow_pt_eff[13] = 0.7255054136119568;
    energyflow_pt_eff[14] = 0.7791239317476077;
    
    TGraph* energyflow_gr_pt = new TGraph(15, pt_bin, energyflow_pt_eff);
    energyflow_gr_pt->SetTitle(0);
    energyflow_gr_pt->GetXaxis()->SetTitle("p_{T}[GeV]");
    energyflow_gr_pt->GetYaxis()->SetTitle("Gluon Jet Rejection Rate");
    energyflow_gr_pt->GetYaxis()->SetRangeUser(0, 0.91);
    energyflow_gr_pt->GetXaxis()->SetRangeUser(0,5000);
    energyflow_gr_pt->SetMarkerColor(41);
    energyflow_gr_pt->SetLineColor(41);
    energyflow_gr_pt->SetLineWidth(2);
    energyflow_gr_pt->SetMarkerStyle(8);
    
    
    
    
    double gluon_rej_DNN_CNN[15];
    gluon_rej_DNN_CNN[0] = 0.34098956556648696;
    gluon_rej_DNN_CNN[1] = 0.5712606651707957;
    gluon_rej_DNN_CNN[2] = 0.6629036172239029;
    gluon_rej_DNN_CNN[3] = 0.6748141027353093;
    gluon_rej_DNN_CNN[4] = 0.6838965229690082;
    gluon_rej_DNN_CNN[5] = 0.6905958147569109;
    gluon_rej_DNN_CNN[6] = 0.6901504664425031;
    gluon_rej_DNN_CNN[7] = 0.6917855288855659;
    gluon_rej_DNN_CNN[8] = 0.6917319239388275;
    gluon_rej_DNN_CNN[9] = 0.6917434528878792;
    gluon_rej_DNN_CNN[10] = 0.6896414807219708;
    gluon_rej_DNN_CNN[11] = 0.6923673278642547;
    gluon_rej_DNN_CNN[12] = 0.6867792430468902;
    gluon_rej_DNN_CNN[13] = 0.6905840513294829;
    gluon_rej_DNN_CNN[14] = 0.7453666101152863;
    
    TGraph* gr_DNN_CNN = new TGraph(15, pt_bin , gluon_rej_DNN_CNN);
    gr_DNN_CNN->SetTitle(0);
    gr_DNN_CNN->GetXaxis()->SetTitle("p_{T}[GeV]");
    gr_DNN_CNN->GetYaxis()->SetTitle("Gluon rejection Rate");
    gr_DNN_CNN->SetMarkerStyle(8);
    gr_DNN_CNN->SetMarkerColor(30);
    gr_DNN_CNN->SetLineColor(30);
    gr_DNN_CNN->SetLineStyle(1);
    gr_DNN_CNN->SetLineWidth(2);
    
    
    double gluon_rej_DNN[15];
    gluon_rej_DNN[0] = 0.3266596036237368;
    gluon_rej_DNN[1] = 0.5567907084769043;
    gluon_rej_DNN[2] = 0.6259326742972494;
    gluon_rej_DNN[3] = 0.6390167314288302;
    gluon_rej_DNN[4] = 0.6469878111389322;
    gluon_rej_DNN[5] = 0.6532314988895443;
    gluon_rej_DNN[6] = 0.6536155511094028;
    gluon_rej_DNN[7] = 0.6553835599640919;
    gluon_rej_DNN[8] = 0.6567781611138709;
    gluon_rej_DNN[9] = 0.6575768686774521;
    gluon_rej_DNN[10] = 0.6588681660378013;
    gluon_rej_DNN[11] = 0.666032045750672;
    gluon_rej_DNN[12] = 0.6633740885662713;
    gluon_rej_DNN[13] = 0.6693847969769495;
    gluon_rej_DNN[14] = 0.7302247091135666;
    
    TGraph* gr_DNN = new TGraph(15, pt_bin , gluon_rej_DNN);
    gr_DNN->SetTitle(0);
    gr_DNN->SetMarkerStyle(8);
    gr_DNN->SetMarkerColor(kBlack);
    gr_DNN->SetLineColor(kBlack);
    gr_DNN->SetLineStyle(1);
    gr_DNN->SetLineWidth(2);
    
    double gluon_rej_CNN[15];
    gluon_rej_CNN[0] = 0.3345114794320576;
    gluon_rej_CNN[1] = 0.5224836628905645;
    gluon_rej_CNN[2] = 0.5948813912943094;
    gluon_rej_CNN[3] = 0.5949675438495128;
    gluon_rej_CNN[4] = 0.5952896426870957;
    gluon_rej_CNN[5] = 0.5953388795024387;
    gluon_rej_CNN[6] = 0.5891771627085429;
    gluon_rej_CNN[7] = 0.5864524668985369;
    gluon_rej_CNN[8] = 0.583786736531039;
    gluon_rej_CNN[9] = 0.5813731990772537;
    gluon_rej_CNN[10] = 0.5736485114970571;
    gluon_rej_CNN[11] = 0.5720589424383682;
    gluon_rej_CNN[12] = 0.5631694258439643;
    gluon_rej_CNN[13] = 0.5663324686654633;
    gluon_rej_CNN[14] = 0.6271864154103777;
    
    TGraph* gr_CNN = new TGraph(15, pt_bin , gluon_rej_CNN);
    gr_CNN->SetTitle(0);
    gr_CNN->SetMarkerStyle(8);
    gr_CNN->SetMarkerColor(kBlue);
    gr_CNN->SetLineColor(kBlue);
    gr_CNN->SetLineStyle(1);
    gr_CNN->SetLineWidth(2);
    
    //BDT
    double gluon_rej_BDT[15];
    gluon_rej_BDT[0] = 0.3372096;
    gluon_rej_BDT[1] = 0.5508908;
    gluon_rej_BDT[2] = 0.5848185;
    gluon_rej_BDT[3] = 0.59964;
    gluon_rej_BDT[4] = 0.6127851;
    gluon_rej_BDT[5] = 0.630227;
    gluon_rej_BDT[6] = 0.6377283;
    gluon_rej_BDT[7] = 0.6470847;
    gluon_rej_BDT[8] = 0.6549175;
    gluon_rej_BDT[9] = 0.6604278;
    gluon_rej_BDT[10] = 0.6689531;
    gluon_rej_BDT[11] = 0.6782608;
    gluon_rej_BDT[12] = 0.6736373;
    gluon_rej_BDT[13] = 0.6737882;
    gluon_rej_BDT[14] = 0.7146442;
    
    TGraph* gr_BDT = new TGraph(15, pt_bin , gluon_rej_BDT);
    gr_BDT->SetTitle(0);
    gr_BDT->SetMarkerStyle(8);
    gr_BDT->SetMarkerColor(48);
    gr_BDT->SetLineColor(48);
    gr_BDT->SetLineStyle(9);
    gr_BDT->SetLineWidth(2);
    
    
    
    TGraph* gr_pt = new TGraph(15, pt_bin, pt_eff);
    gr_pt->SetTitle(0);
    gr_pt->GetXaxis()->SetTitle("p_{T}[GeV]");
    gr_pt->GetYaxis()->SetTitle("Gluon Jet Rejection Rate");
    gr_pt->GetYaxis()->SetRangeUser(0, 0.91);
    gr_pt->GetXaxis()->SetRangeUser(0,5000);
    gr_pt->SetMarkerStyle(8);
    gr_pt->SetMarkerColor(kRed);
    gr_pt->SetLineColor(kRed);
    gr_pt->SetLineStyle(8);
    gr_pt->SetLineWidth(2);
    //gr_pt->Draw("APL");
    flat_gr_pt->Draw("APL");
    energyflow_gr_pt->Draw("SAMEPL");
    gr_DNN_CNN->Draw("SAMEPL");
    gr_DNN->Draw("SAMEPL");
    gr_CNN->Draw("samePL");
    gr_BDT->Draw("samePL");
    
    TLatex latex_pt;
    latex_pt.SetTextSize(0.038);
    latex_pt.SetTextAlign(13);  //align at top
    latex_pt.DrawLatex(250, 0.89,"#it{ATLAS} #bf{Simulation Work in progress}");
    latex_pt.DrawLatex(250, 0.85,"#bf{Gluon Rejection Rate @80% Quark Efficiency Rate}");
    latex_pt.SetTextSize(0.03);
    latex_pt.DrawLatex(250, 0.805,"#bf{#sqrt{s} = 13 TeV}");
    latex_pt.DrawLatex(250, 0.775,"#bf{Small-R Jet (Anti-k_{t} R=0.4)}");
    latex_pt.DrawLatex(250, 0.745,"#bf{|#eta|<2.1, p_{T}>25 GeV}");
    
    TLegend* leg1 = new TLegend(0.15,0.15,0.50,0.35);
    leg1->SetTextSize(0.045);
    leg1->SetBorderSize(0);
    leg1->SetFillStyle(0);
    leg1->AddEntry(flat_gr_pt,"Deep Sets Tagger");
    leg1->AddEntry(energyflow_gr_pt,"Energy Flow Tagger");
    leg1->AddEntry(gr_DNN_CNN,"MLP_CNN Tagger");
    leg1->AddEntry(gr_CNN,"CNN Tagger");
    leg1->AddEntry(gr_DNN,"MLP Tagger");
    leg1->AddEntry(gr_BDT,"BDT Tagger");
    leg1->Draw("same");
    c1->SaveAs("conv1d_pt_eff.eps");
    
    
    
    //eta
    TCanvas* c2 = new TCanvas("c2","c2",50,50,640,490);
    c2->SetLeftMargin(0.13);
    c2->SetTickx(1);
    c2->SetTicky(1);
    //c1->SetLogy();
    
    double eta_eff[4];
    double eta_bin[4];
    
    eta_eff[0] = 0.7886864205721887;
    eta_eff[1] = 0.7157236465582353;
    eta_eff[2] = 0.677749557367515;
    eta_eff[3] = 0.6250240225461523;
    
    eta_bin[0] = 0.25;
    eta_bin[1] = 0.75;
    eta_bin[2] = 1.25;
    eta_bin[3] = 1.8;
    
    //conv1d_eta
    double flat_eta_eff[4];
    flat_eta_eff[0] = 0.7719134718611141;
    flat_eta_eff[1] = 0.7116669817445327;
    flat_eta_eff[2] = 0.6705522862680985;
    flat_eta_eff[3] = 0.6278668421528624;
    
    TGraph* flat_gr_eta = new TGraph(4, eta_bin, flat_eta_eff);
    flat_gr_eta->SetTitle(0);
    flat_gr_eta->SetMarkerStyle(8);
    flat_gr_eta->GetXaxis()->SetTitle("|#eta|");
    flat_gr_eta->GetYaxis()->SetTitle("Gluon Jet Rejection Rate");
    flat_gr_eta->GetYaxis()->SetRangeUser(0.3,0.9);
    flat_gr_eta->GetXaxis()->SetRangeUser(0,2.1);
    flat_gr_eta->SetMarkerColor(kRed);
    flat_gr_eta->SetLineColor(kRed);
    flat_gr_eta->SetLineWidth(2);
    
    
    //energyflow
    double energyflow_eta_eff[4];
    energyflow_eta_eff[0] = 0.7696443401386153;
    energyflow_eta_eff[1] = 0.7035558618279462;
    energyflow_eta_eff[2] = 0.665616856288203;
    energyflow_eta_eff[3] = 0.6214113700713856;
    
    TGraph* energyflow_gr_eta = new TGraph(4, eta_bin, energyflow_eta_eff);
    energyflow_gr_eta->SetTitle(0);
    energyflow_gr_eta->SetMarkerStyle(8);
    energyflow_gr_eta->GetXaxis()->SetTitle("|#eta|");
    energyflow_gr_eta->GetYaxis()->SetTitle("Gluon Jet Rejection Rate");
    energyflow_gr_eta->GetYaxis()->SetRangeUser(0.3,0.9);
    energyflow_gr_eta->GetXaxis()->SetRangeUser(0,2.1);
    energyflow_gr_eta->SetMarkerColor(41);
    energyflow_gr_eta->SetLineColor(41);
    energyflow_gr_eta->SetLineWidth(2);
    
    
    
    
    
    double eta_gluon_rej_DNN_CNN[4];
    eta_gluon_rej_DNN_CNN[0] = 0.7480907744937828;
    eta_gluon_rej_DNN_CNN[1] = 0.6873436176352333;
    eta_gluon_rej_DNN_CNN[2] = 0.6560107254223464;
    eta_gluon_rej_DNN_CNN[3] = 0.6053775105983229;
    
    TGraph* eta_gr_DNN_CNN = new TGraph(4, eta_bin , eta_gluon_rej_DNN_CNN);
    eta_gr_DNN_CNN->SetTitle(0);
    //c1->SetLogx();
    eta_gr_DNN_CNN->SetMarkerStyle(8);
    eta_gr_DNN_CNN->SetMarkerColor(30);
    eta_gr_DNN_CNN->SetLineColor(30);
    eta_gr_DNN_CNN->SetLineStyle(1);
    eta_gr_DNN_CNN->SetLineWidth(2);
    
    double eta_gluon_rej_DNN[4];
    eta_gluon_rej_DNN[0] = 0.7193833724243105;
    eta_gluon_rej_DNN[1] = 0.6560520991324161;
    eta_gluon_rej_DNN[2] = 0.6239931943264356;
    eta_gluon_rej_DNN[3] = 0.5908868794996773;
    

    TGraph* eta_gr_DNN = new TGraph(4, eta_bin , eta_gluon_rej_DNN);
    eta_gr_DNN->SetTitle(0);
    eta_gr_DNN->SetMarkerStyle(8);
    eta_gr_DNN->SetMarkerColor(kBlack);
    eta_gr_DNN->SetLineColor(kBlack);
    eta_gr_DNN->SetLineStyle(1);
    eta_gr_DNN->SetLineWidth(2);

    double eta_gluon_rej_CNN[4];
    
    eta_gluon_rej_CNN[0] = 0.6250935566394715;
    eta_gluon_rej_CNN[1] = 0.5559540739934181;
    eta_gluon_rej_CNN[2] = 0.541;
    eta_gluon_rej_CNN[3] = 0.533;

    
    TGraph* eta_gr_CNN = new TGraph(4, eta_bin , eta_gluon_rej_CNN);
    eta_gr_CNN->SetTitle(0);
    eta_gr_CNN->SetMarkerStyle(8);
    eta_gr_CNN->SetMarkerColor(kBlue);
    eta_gr_CNN->SetLineColor(kBlue);
    eta_gr_CNN->SetLineStyle(1);
    eta_gr_CNN->SetLineWidth(2);
    
    double eta_gluon_rej_BDT[4];
    
    eta_gluon_rej_BDT[0] = 0.6996583;
    eta_gluon_rej_BDT[1] = 0.6536351;
    eta_gluon_rej_BDT[2] = 0.6182201;
    eta_gluon_rej_BDT[3] = 0.5789896;

    
    TGraph* eta_gr_BDT = new TGraph(4, eta_bin , eta_gluon_rej_BDT);
    eta_gr_BDT->SetTitle(0);
    eta_gr_BDT->SetMarkerStyle(8);
    eta_gr_BDT->SetMarkerColor(48);
    eta_gr_BDT->SetLineColor(48);
    eta_gr_BDT->SetLineStyle(9);
    eta_gr_BDT->SetLineWidth(2);
    
    
    TGraph* gr_eta = new TGraph(4, eta_bin, eta_eff);
    gr_eta->SetTitle(0);
    gr_eta->GetXaxis()->SetTitle("|#eta|");
    gr_eta->GetYaxis()->SetTitle("Gluon Jet Rejection");
    gr_eta->GetYaxis()->SetRangeUser(0.3,0.9);
    gr_eta->GetXaxis()->SetRangeUser(0,2.1);
    gr_eta->SetMarkerStyle(8);
    gr_eta->SetMarkerColor(kRed);
    gr_eta->SetLineColor(kRed);
    gr_eta->SetLineWidth(2);
    //gr_eta->Draw("APL");
    flat_gr_eta->Draw("APL");
    energyflow_gr_eta->Draw("SAMEPL");
    eta_gr_DNN_CNN->Draw("SAMEPL");
    eta_gr_DNN->Draw("SAMEPL");
    eta_gr_CNN->Draw("samePL");
    eta_gr_BDT->Draw("samePL");
    
    TLatex latex_eta;
    latex_eta.SetTextSize(0.038);
    latex_eta.SetTextAlign(13);  //align at top
    latex_eta.DrawLatex(0.80, 0.88,"#it{ATLAS} #bf{Simulation Work in progress}");
    latex_pt.DrawLatex(0.80, 0.85,"#bf{Gluon Rejection Rate @80% Quark Efficiency Rate}");
    latex_eta.SetTextSize(0.03);
    latex_eta.DrawLatex(0.80, 0.82,"#bf{#sqrt{s} = 13 TeV}");
    latex_eta.DrawLatex(0.80, 0.795,"#bf{Small-R Jet (Anti-k_{t} R=0.4)}");
    latex_eta.DrawLatex(0.80, 0.770,"#bf{p_{T}>25 GeV}");
    
    TLegend* leg2 = new TLegend(0.15,0.15,0.50,0.35);
    leg2->SetTextSize(0.045);
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
    leg2->AddEntry(flat_gr_eta,"Deep Sets Tagger");
    leg2->AddEntry(energyflow_gr_eta,"Energy Flow Tagger");
    leg2->AddEntry(eta_gr_DNN_CNN,"MLP_CNN Tagger");
    leg2->AddEntry(eta_gr_CNN,"CNN Tagger");
    leg2->AddEntry(eta_gr_DNN,"MLP Tagger");
    leg2->AddEntry(eta_gr_BDT,"BDT Tagger");
    leg2->Draw("same");
    
    c2->SaveAs("conv1d_eta_eff.eps");
    
    
}
