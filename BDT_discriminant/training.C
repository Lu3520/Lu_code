{
  // Open an input file for training and test:
  // NB: To avoid basket's WriteBuffer full problem, the input file pointer of TFile should be obtained before opening outputFile.
  //TFile* signal_file = TFile::Open("../signal/output/VBS.root");
  //TFile* bkg_lep_flie = TFile::Open("../bkg/output/lep.root");
  //TFile* bkg_ttbar_file = TFile::Open("../ttbar_nonallhad_bkg/output/ttbar.root");
  TFile* signal_file = TFile::Open("limit_minmass/neural/VBS_minmass.root");
  TFile* bkg_lep_flie = TFile::Open("limit_minmass/neural/lep_minmass.root");
  TFile* bkg_ttbar_file = TFile::Open("limit_minmass/neural/ttbar_minmass.root");

  //TFile* signal_file = TFile::Open("/home/chengyu/paper/VBS/neural_network/output/score_output/signal/output/VBS.root");
  //TFile* bkg_lep_flie = TFile::Open("/home/chengyu/paper/VBS/neural_network/output/score_output/bkg/output/lep.root");
  //TFile* bkg_ttbar_file = TFile::Open("/home/chengyu/paper/VBS/neural_network/output/score_output/ttbar_nonallhad_bkg/output/ttbar.root");
    
    
    
  std::cout << "--- TMVAClassification   : Using input signal file: " << signal_file->GetName() << std::endl;
  std::cout << "--- TMVAClassification   : Using input Background file: " << bkg_lep_flie->GetName() << std::endl;
  std::cout << "--- TMVAClassification   : Using input Background file: " << bkg_ttbar_file->GetName() << std::endl;
    
  // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
  TString outfileName("TMVA.root");
  TFile* outputFile = TFile::Open(outfileName, "RECREATE");
    
  // Create the factory object
  //TMVA::Factory* factory = new TMVA::Factory("TMVAClassification", outputFile,
  //"!V:!Silent:Color:!DrawProgressBar:AnalysisType=Classification");
    
  // Define the input variables that shall be used for the MVA training
  // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
  TMVA::DataLoader* dataloader = new TMVA::DataLoader("Dataset");
  dataloader->AddVariable("mtagjj", 'F' );
  dataloader->AddVariable("detatagjj", 'F');
  dataloader->AddVariable("pttagj1", 'F');
  dataloader->AddVariable("pttagj2",  'F');
  dataloader->AddVariable("detajj", 'F');
  dataloader->AddVariable("ptj1", 'F');
  dataloader->AddVariable("ptj2",  'F');
  dataloader->AddVariable("widthj1", 'F' );
  dataloader->AddVariable("widthj2", 'F');
  dataloader->AddVariable("ntrackj1", 'F');
  dataloader->AddVariable("ntrackj2",  'F');
  dataloader->AddVariable("widthtagj1", 'F');
  dataloader->AddVariable("widthtagj2", 'F');
  dataloader->AddVariable("ntracktagj1",  'F');
  dataloader->AddVariable("ntracktagj2", 'F' );
  dataloader->AddVariable("num_trkj", 'F');
  dataloader->AddVariable("num_extraj", 'F');
  dataloader->AddVariable("met",  'F');
  dataloader->AddVariable("etal", 'F');
  dataloader->AddVariable("deltaRlnu", 'F');
  dataloader->AddVariable("centrality",  'F');
  dataloader->AddVariable("mVV", 'F');
  dataloader->AddVariable("mVVjj",  'F');
  //dataloader->AddVariable("probtagj1_neural", 'F');
  //dataloader->AddVariable("probtagj2_neural", 'F');
  //dataloader->AddVariable("probj1_neural", 'F');
  //dataloader->AddVariable("probj2_neural", 'F');
    
  dataloader->AddSpectator("evtNum", 'F');

  // --- Register the training and test trees
  /*TTree* t_sig = (TTree*)signal_file->Get("BDTinput_2leading");
    
  TTree* bkg_lep = (TTree*)bkg_lep_flie->Get("BDTinput_2leading");
  TTree* bkg_ttbar = (TTree*)bkg_ttbar_file->Get("BDTinput_2leading");*/
        
  TTree* t_sig = (TTree*)signal_file->Get("BDTinput_minmass");
    
  TTree* bkg_lep = (TTree*)bkg_lep_flie->Get("BDTinput_minmass");
  TTree* bkg_ttbar = (TTree*)bkg_ttbar_file->Get("BDTinput_minmass");

  /*TTree* t_sig = (TTree*)signal_file->Get("BDTinput_neural");
    
  TTree* bkg_lep = (TTree*)bkg_lep_flie->Get("BDTinput_neural");
  TTree* bkg_ttbar = (TTree*)bkg_ttbar_file->Get("BDTinput_neural");*/

  /*TTree* t_sig = (TTree*)signal_file->Get("BDTinput_neural");
    
  TTree* bkg_lep = (TTree*)bkg_lep_flie->Get("BDTinput_neural");
  TTree* bkg_ttbar = (TTree*)bkg_ttbar_file->Get("BDTinput_neural");*/
    
  // global event weights per tree (see below for setting event-wise weights)
    
  
  // You can add an arbitrary number of signal or background trees
  //weight = crossection/sumOfweight
    
  Double_t globalweight = 1.0;
  TCut cuts = "";

  dataloader->AddSignalTree(t_sig, 1.0);
  dataloader->AddBackgroundTree(bkg_lep, 1.0);
  dataloader->AddBackgroundTree(bkg_ttbar, 1.0);
  
  // Set individual event weights (the variables must exist in the original TTree)
  dataloader->SetSignalWeightExpression("weight");
  dataloader->SetBackgroundWeightExpression("weight");
    
  // Apply additional cuts on the signal and background samples (can be different)
  TCut mycut = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
  TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";
    
  // Tell the factory how to use the training and testing events
  dataloader->PrepareTrainingAndTestTree("", "",
					 "nTest_Signal=1"
					 ":nTest_Background=1"
					 ":SplitMode=Random"
					 ":NormMode=NumEvents"
					 ":!V");
    
  // ---- Book MVA methods
  //Cut optimisation
  // factory->BookMethod(dataloader, TMVA::Types::kCuts, "Cuts",
  //              "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
    
  // Likelihood ("naive Bayes estimator")
  //factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "Likelihood",
  //              "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50");
    
  // Test the multi-dimensional probability density estimator
  // here are the options strings for the MinMax and RMS methods, respectively:
  //factory->BookMethod(dataloader, TMVA::Types::kPDERS, "PDERS",
  //              "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600");


  UInt_t numFolds = 2;
  TString analysisType = "Classification";
  TString splitType ="Deterministic";
  float NumFolds = 2;
  TString splitExpr = "int(fabs([evtNum]))%int([NumFolds])";

  TString cvOptions = Form("!V"
			   ":!Silent"
			   ":ModelPersistence"
			   ":AnalysisType=%s"
			   ":SplitType=%s"
			   ":NumFolds=%i"
			   ":SplitExpr=%s",
			   analysisType.Data(), splitType.Data(), numFolds,
			   splitExpr.Data());
 
  TMVA::CrossValidation cv{"TMVACrossValidation", dataloader, outputFile, cvOptions};
  //cv.SetNumFolds(3);

  // Boosted Decision Trees
  cv.BookMethod(TMVA::Types::kBDT, "BDT",
		"!H:!V:NTrees=800:MinNodeSize=5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20:Shrinkage=0.3");

    
  //rule fit
  //factory->BookMethod(dataloader, TMVA::Types::kRuleFit, "RuleFit",
  //              "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );
    
 
  cv.Evaluate();

  // ---- Now you can tell the factory to train, test, and evaluate the MVAs
  // Train MVAs using the set of training events
  /*cv.TrainAllMethods();
  // ---- Evaluate all MVAs using the set of test events
  cv.TestAllMethods();
  // ----- Evaluate and compare performance of all configured MVAs
  cv.EvaluateAllMethods();*/
    
  // Save the output
  outputFile->Close();
    
  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;
    
  //delete factory;
}

