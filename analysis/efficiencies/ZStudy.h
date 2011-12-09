//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 28 18:03:19 2011 by ROOT version 5.28/00b
// from TTree Z1/
// found on file: output.root
//////////////////////////////////////////////////////////

#ifndef ZStudy_h
#define ZStudy_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class ZStudy {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           RunNumber;
   Int_t           EventNumber;
   Int_t           LumiBlock;
   Float_t         actualIntPerXing;
   Float_t         averageIntPerXing;
   Int_t           elTrigger;
   Int_t           muTrigger;
   Int_t           tn;
   UInt_t          ta[1];   //[tn]
   Int_t           n;
   Int_t           nPV2;
   Float_t         weight[2];   //[n]
   Int_t           l1_tight[2];   //[n]
   Int_t           l2_tight[2];   //[n]
   Int_t           l1_truthMatch[2];   //[n]
   Int_t           l2_truthMatch[2];   //[n]
   Int_t           l1_triggerMatch[2];   //[n]
   Int_t           l2_triggerMatch[2];   //[n]
   Float_t         l1_pt[2];   //[n]
   Float_t         l2_pt[2];   //[n]
   Float_t         l1_eta[2];   //[n]
   Float_t         l2_eta[2];   //[n]
   Float_t         l1_phi[2];   //[n]
   Float_t         l2_phi[2];   //[n]
   Float_t         l1_tkIso20[2];   //[n]
   Float_t         l2_tkIso20[2];   //[n]
   Float_t         l1_tkIso30[2];   //[n]
   Float_t         l2_tkIso30[2];   //[n]
   Float_t         l1_clIso20[2];   //[n]
   Float_t         l2_clIso20[2];   //[n]
   Float_t         l1_clIso30[2];   //[n]
   Float_t         l2_clIso30[2];   //[n]
   Float_t         l1_clIso20_corrected[2];   //[n]
   Float_t         l2_clIso20_corrected[2];   //[n]
   Float_t         l1_clIso30_corrected[2];   //[n]
   Float_t         l2_clIso30_corrected[2];   //[n]
   Float_t         l1_d0sigma[2];   //[n]
   Float_t         l2_d0sigma[2];   //[n]
   Float_t         Z_m[2];   //[n]
   Float_t         Z_et[2];   //[n]
   Float_t         Z_pt[2];   //[n]
   Float_t         Z_eta[2];   //[n]
   Float_t         Z_phi[2];   //[n]

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_LumiBlock;   //!
   TBranch        *b_actualIntPerXing;   //!
   TBranch        *b_averageIntPerXing;   //!
   TBranch        *b_elTrigger;   //!
   TBranch        *b_muTrigger;   //!
   TBranch        *b_tn;   //!
   TBranch        *b_ta;   //!
   TBranch        *b_n;   //!
   TBranch        *b_nPV2;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_l1_tight;   //!
   TBranch        *b_l2_tight;   //!
   TBranch        *b_l1_truthMatch;   //!
   TBranch        *b_l2_truthMatch;   //!
   TBranch        *b_l1_triggerMatch;   //!
   TBranch        *b_l2_triggerMatch;   //!
   TBranch        *b_l1_pt;   //!
   TBranch        *b_l2_pt;   //!
   TBranch        *b_l1_eta;   //!
   TBranch        *b_l2_eta;   //!
   TBranch        *b_l1_phi;   //!
   TBranch        *b_l2_phi;   //!
   TBranch        *b_l1_tkIso20;   //!
   TBranch        *b_l2_tkIso20;   //!
   TBranch        *b_l1_tkIso30;   //!
   TBranch        *b_l2_tkIso30;   //!
   TBranch        *b_l1_clIso20;   //!
   TBranch        *b_l2_clIso20;   //!
   TBranch        *b_l1_clIso30;   //!
   TBranch        *b_l2_clIso30;   //!
   TBranch        *b_l1_clIso20_corrected;   //!
   TBranch        *b_l2_clIso20_corrected;   //!
   TBranch        *b_l1_clIso30_corrected;   //!
   TBranch        *b_l2_clIso30_corrected;   //!
   TBranch        *b_l1_d0sigma;   //!
   TBranch        *b_l2_d0sigma;   //!
   TBranch        *b_Z_m;   //!
   TBranch        *b_Z_et;   //!
   TBranch        *b_Z_pt;   //!
   TBranch        *b_Z_eta;   //!
   TBranch        *b_Z_phi;   //!

   ZStudy(TTree *tree=0);
   virtual ~ZStudy();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ZStudy_cxx
ZStudy::ZStudy(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output.root");
      if (!f) {
         f = new TFile("output.root");
      }
      tree = (TTree*)gDirectory->Get("Z1");

   }
   Init(tree);
}

ZStudy::~ZStudy()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ZStudy::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ZStudy::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ZStudy::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("LumiBlock", &LumiBlock, &b_LumiBlock);
   fChain->SetBranchAddress("actualIntPerXing", &actualIntPerXing, &b_actualIntPerXing);
   fChain->SetBranchAddress("averageIntPerXing", &averageIntPerXing, &b_averageIntPerXing);
   fChain->SetBranchAddress("elTrigger", &elTrigger, &b_elTrigger);
   fChain->SetBranchAddress("muTrigger", &muTrigger, &b_muTrigger);
   fChain->SetBranchAddress("tn", &tn, &b_tn);
   fChain->SetBranchAddress("ta", &ta, &b_ta);
   fChain->SetBranchAddress("n", &n, &b_n);
   fChain->SetBranchAddress("nPV2", &nPV2, &b_nPV2);
   fChain->SetBranchAddress("weight", weight, &b_weight);
   fChain->SetBranchAddress("l1_tight", l1_tight, &b_l1_tight);
   fChain->SetBranchAddress("l2_tight", l2_tight, &b_l2_tight);
   fChain->SetBranchAddress("l1_truthMatch", l1_truthMatch, &b_l1_truthMatch);
   fChain->SetBranchAddress("l2_truthMatch", l2_truthMatch, &b_l2_truthMatch);
   fChain->SetBranchAddress("l1_triggerMatch", l1_triggerMatch, &b_l1_triggerMatch);
   fChain->SetBranchAddress("l2_triggerMatch", l2_triggerMatch, &b_l2_triggerMatch);
   fChain->SetBranchAddress("l1_pt", l1_pt, &b_l1_pt);
   fChain->SetBranchAddress("l2_pt", l2_pt, &b_l2_pt);
   fChain->SetBranchAddress("l1_eta", l1_eta, &b_l1_eta);
   fChain->SetBranchAddress("l2_eta", l2_eta, &b_l2_eta);
   fChain->SetBranchAddress("l1_phi", l1_phi, &b_l1_phi);
   fChain->SetBranchAddress("l2_phi", l2_phi, &b_l2_phi);
   fChain->SetBranchAddress("l1_tkIso20", l1_tkIso20, &b_l1_tkIso20);
   fChain->SetBranchAddress("l2_tkIso20", l2_tkIso20, &b_l2_tkIso20);
   fChain->SetBranchAddress("l1_tkIso30", l1_tkIso30, &b_l1_tkIso30);
   fChain->SetBranchAddress("l2_tkIso30", l2_tkIso30, &b_l2_tkIso30);
   fChain->SetBranchAddress("l1_clIso20", l1_clIso20, &b_l1_clIso20);
   fChain->SetBranchAddress("l2_clIso20", l2_clIso20, &b_l2_clIso20);
   fChain->SetBranchAddress("l1_clIso30", l1_clIso30, &b_l1_clIso30);
   fChain->SetBranchAddress("l2_clIso30", l2_clIso30, &b_l2_clIso30);
   fChain->SetBranchAddress("l1_clIso20_corrected", l1_clIso20_corrected, &b_l1_clIso20_corrected);
   fChain->SetBranchAddress("l2_clIso20_corrected", l2_clIso20_corrected, &b_l2_clIso20_corrected);
   fChain->SetBranchAddress("l1_clIso30_corrected", l1_clIso30_corrected, &b_l1_clIso30_corrected);
   fChain->SetBranchAddress("l2_clIso30_corrected", l2_clIso30_corrected, &b_l2_clIso30_corrected);
   fChain->SetBranchAddress("l1_d0sigma", l1_d0sigma, &b_l1_d0sigma);
   fChain->SetBranchAddress("l2_d0sigma", l2_d0sigma, &b_l2_d0sigma);
   fChain->SetBranchAddress("Z_m", Z_m, &b_Z_m);
   fChain->SetBranchAddress("Z_et", Z_et, &b_Z_et);
   fChain->SetBranchAddress("Z_pt", Z_pt, &b_Z_pt);
   fChain->SetBranchAddress("Z_eta", Z_eta, &b_Z_eta);
   fChain->SetBranchAddress("Z_phi", Z_phi, &b_Z_phi);
   Notify();
}

Bool_t ZStudy::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ZStudy::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ZStudy::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ZStudy_cxx
