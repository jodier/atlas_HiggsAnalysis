//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 28 01:58:15 2011 by ROOT version 5.28/00g
// from TTree physics/physics
// found on file: result.root
//////////////////////////////////////////////////////////

#ifndef THiggsD3PD_h
#define THiggsD3PD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class THiggsD3PD {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          RunNumber;
   UInt_t          EventNumber;
   UInt_t          lbn;
   Float_t         actualIntPerXing;
   Float_t         averageIntPerXing;
   UInt_t          larError;
   Bool_t          EF_2e12_medium;
   Bool_t          EF_2e12T_medium;
   Bool_t          EF_2e12Tvh_medium;
   Bool_t          EF_2mu10_loose;
   Bool_t          EF_e20_medium;
   Bool_t          EF_e22_medium;
   Bool_t          EF_e22_medium1;
   Bool_t          EF_e22vh_medium1;
   Bool_t          EF_mu18_MG;
   Bool_t          EF_mu18_MG_medium;
   Int_t           el_n;
   std::vector<float>   *el_charge;
   std::vector<int>     *el_author;
   std::vector<unsigned int> *el_OQ;
   std::vector<int>     *el_medium;
   std::vector<int>     *el_tight;
   std::vector<int>     *el_loosePP;
   std::vector<float>   *el_Etcone20;
   std::vector<float>   *el_Etcone30;
   std::vector<float>   *el_ptcone20;
   std::vector<float>   *el_ptcone30;
   std::vector<float>   *el_etap;
   std::vector<float>   *el_etas2;
   std::vector<float>   *el_cl_E;
   std::vector<float>   *el_cl_pt;
   std::vector<float>   *el_cl_eta;
   std::vector<float>   *el_cl_phi;
   std::vector<float>   *el_trackd0;
   std::vector<float>   *el_trackz0;
   std::vector<float>   *el_trackphi;
   std::vector<float>   *el_tracktheta;
   std::vector<float>   *el_trackqoverp;
   std::vector<float>   *el_trackpt;
   std::vector<float>   *el_tracketa;
   std::vector<int>     *el_nPixHits;
   std::vector<int>     *el_nSCTHits;
   std::vector<int>     *el_EF_index;
   std::vector<float>   *el_trackd0pvunbiased;
   std::vector<float>   *el_tracksigd0pvunbiased;
   std::vector<float>   *el_trackz0pvunbiased;
   Int_t           mu_muid_n;
   std::vector<float>   *mu_muid_E;
   std::vector<float>   *mu_muid_pt;
   std::vector<float>   *mu_muid_eta;
   std::vector<float>   *mu_muid_phi;
   std::vector<float>   *mu_muid_charge;
   std::vector<int>     *mu_muid_author;
   std::vector<float>   *mu_muid_etcone20;
   std::vector<float>   *mu_muid_etcone30;
   std::vector<float>   *mu_muid_ptcone20;
   std::vector<float>   *mu_muid_ptcone30;
   std::vector<int>     *mu_muid_isCombinedMuon;
   std::vector<int>     *mu_muid_tight;
   std::vector<float>   *mu_muid_id_theta_exPV;
   std::vector<float>   *mu_muid_id_qoverp_exPV;
   std::vector<float>   *mu_muid_me_theta_exPV;
   std::vector<float>   *mu_muid_me_qoverp_exPV;
   std::vector<float>   *mu_muid_id_d0;
   std::vector<float>   *mu_muid_id_z0;
   std::vector<float>   *mu_muid_id_phi;
   std::vector<float>   *mu_muid_id_theta;
   std::vector<float>   *mu_muid_id_qoverp;
   std::vector<int>     *mu_muid_nBLHits;
   std::vector<int>     *mu_muid_nPixHits;
   std::vector<int>     *mu_muid_nSCTHits;
   std::vector<int>     *mu_muid_nTRTHits;
   std::vector<int>     *mu_muid_nPixHoles;
   std::vector<int>     *mu_muid_nSCTHoles;
   std::vector<int>     *mu_muid_nTRTOutliers;
   std::vector<int>     *mu_muid_nPixelDeadSensors;
   std::vector<int>     *mu_muid_nSCTDeadSensors;
   std::vector<int>     *mu_muid_expectBLayerHit;
   std::vector<float>   *mu_muid_trackd0pvunbiased;
   std::vector<float>   *mu_muid_trackz0pvunbiased;
   std::vector<float>   *mu_muid_tracksigd0pvunbiased;
   std::vector<int>     *mu_muid_EFCB_index;
   Int_t           mu_staco_n;
   std::vector<float>   *mu_staco_E;
   std::vector<float>   *mu_staco_pt;
   std::vector<float>   *mu_staco_eta;
   std::vector<float>   *mu_staco_phi;
   std::vector<float>   *mu_staco_charge;
   std::vector<int>     *mu_staco_author;
   std::vector<float>   *mu_staco_etcone20;
   std::vector<float>   *mu_staco_etcone30;
   std::vector<float>   *mu_staco_ptcone20;
   std::vector<float>   *mu_staco_ptcone30;
   std::vector<int>     *mu_staco_isCombinedMuon;
   std::vector<int>     *mu_staco_tight;
   std::vector<float>   *mu_staco_id_theta_exPV;
   std::vector<float>   *mu_staco_id_qoverp_exPV;
   std::vector<float>   *mu_staco_me_theta_exPV;
   std::vector<float>   *mu_staco_me_qoverp_exPV;
   std::vector<float>   *mu_staco_id_d0;
   std::vector<float>   *mu_staco_id_z0;
   std::vector<float>   *mu_staco_id_phi;
   std::vector<float>   *mu_staco_id_theta;
   std::vector<float>   *mu_staco_id_qoverp;
   std::vector<int>     *mu_staco_nBLHits;
   std::vector<int>     *mu_staco_nPixHits;
   std::vector<int>     *mu_staco_nSCTHits;
   std::vector<int>     *mu_staco_nTRTHits;
   std::vector<int>     *mu_staco_nPixHoles;
   std::vector<int>     *mu_staco_nSCTHoles;
   std::vector<int>     *mu_staco_nTRTOutliers;
   std::vector<int>     *mu_staco_nPixelDeadSensors;
   std::vector<int>     *mu_staco_nSCTDeadSensors;
   std::vector<int>     *mu_staco_expectBLayerHit;
   std::vector<float>   *mu_staco_trackd0pvunbiased;
   std::vector<float>   *mu_staco_trackz0pvunbiased;
   std::vector<float>   *mu_staco_tracksigd0pvunbiased;
   std::vector<int>     *mu_staco_EFCB_index;
   Int_t           vxp_n;
   std::vector<int>     *vxp_nTracks;
   std::vector<int>     *trig_EF_trigmugirl_EF_2mu10_loose;
   std::vector<int>     *trig_EF_trigmugirl_EF_mu18_MG;
   std::vector<int>     *trig_EF_trigmugirl_track_n;
   std::vector<std::vector<float> > *trig_EF_trigmugirl_track_CB_eta;
   std::vector<std::vector<float> > *trig_EF_trigmugirl_track_CB_phi;
   Int_t           trig_EF_el_n;
   std::vector<float>   *trig_EF_el_eta;
   std::vector<float>   *trig_EF_el_phi;
   std::vector<int>     *trig_EF_el_EF_2e12_medium;
   std::vector<int>     *trig_EF_el_EF_e20_medium;
   std::vector<int>     *trig_EF_el_EF_e22_medium;

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_actualIntPerXing;   //!
   TBranch        *b_averageIntPerXing;   //!
   TBranch        *b_larError;   //!
   TBranch        *b_EF_2e12_medium;   //!
   TBranch        *b_EF_2e12T_medium;   //!
   TBranch        *b_EF_2e12Tvh_medium;   //!
   TBranch        *b_EF_2mu10_loose;   //!
   TBranch        *b_EF_e20_medium;   //!
   TBranch        *b_EF_e22_medium;   //!
   TBranch        *b_EF_e22_medium1;   //!
   TBranch        *b_EF_e22vh_medium1;   //!
   TBranch        *b_EF_mu18_MG;   //!
   TBranch        *b_EF_mu18_MG_medium;   //!
   TBranch        *b_el_GSF_n;   //!
   TBranch        *b_el_GSF_charge;   //!
   TBranch        *b_el_GSF_author;   //!
   TBranch        *b_el_GSF_OQ;   //!
   TBranch        *b_el_GSF_medium;   //!
   TBranch        *b_el_GSF_tight;   //!
   TBranch        *b_el_GSF_loosePP;   //!
   TBranch        *b_el_GSF_Etcone20;   //!
   TBranch        *b_el_GSF_Etcone30;   //!
   TBranch        *b_el_GSF_ptcone20;   //!
   TBranch        *b_el_GSF_ptcone30;   //!
   TBranch        *b_el_GSF_etap;   //!
   TBranch        *b_el_GSF_etas2;   //!
   TBranch        *b_el_GSF_cl_E;   //!
   TBranch        *b_el_GSF_cl_pt;   //!
   TBranch        *b_el_GSF_cl_eta;   //!
   TBranch        *b_el_GSF_cl_phi;   //!
   TBranch        *b_el_GSF_trackd0;   //!
   TBranch        *b_el_GSF_trackz0;   //!
   TBranch        *b_el_GSF_trackphi;   //!
   TBranch        *b_el_GSF_tracktheta;   //!
   TBranch        *b_el_GSF_trackqoverp;   //!
   TBranch        *b_el_GSF_trackpt;   //!
   TBranch        *b_el_GSF_tracketa;   //!
   TBranch        *b_el_GSF_nPixHits;   //!
   TBranch        *b_el_GSF_nSCTHits;   //!
   TBranch        *b_el_GSF_EF_index;   //!
   TBranch        *b_el_GSF_trackd0pvunbiased;   //!
   TBranch        *b_el_GSF_tracksigd0pvunbiased;   //!
   TBranch        *b_el_GSF_trackz0pvunbiased;   //!
   TBranch        *b_mu_muid_n;   //!
   TBranch        *b_mu_muid_E;   //!
   TBranch        *b_mu_muid_pt;   //!
   TBranch        *b_mu_muid_eta;   //!
   TBranch        *b_mu_muid_phi;   //!
   TBranch        *b_mu_muid_charge;   //!
   TBranch        *b_mu_muid_author;   //!
   TBranch        *b_mu_muid_etcone20;   //!
   TBranch        *b_mu_muid_etcone30;   //!
   TBranch        *b_mu_muid_ptcone20;   //!
   TBranch        *b_mu_muid_ptcone30;   //!
   TBranch        *b_mu_muid_isCombinedMuon;   //!
   TBranch        *b_mu_muid_tight;   //!
   TBranch        *b_mu_muid_id_theta_exPV;   //!
   TBranch        *b_mu_muid_id_qoverp_exPV;   //!
   TBranch        *b_mu_muid_me_theta_exPV;   //!
   TBranch        *b_mu_muid_me_qoverp_exPV;   //!
   TBranch        *b_mu_muid_id_d0;   //!
   TBranch        *b_mu_muid_id_z0;   //!
   TBranch        *b_mu_muid_id_phi;   //!
   TBranch        *b_mu_muid_id_theta;   //!
   TBranch        *b_mu_muid_id_qoverp;   //!
   TBranch        *b_mu_muid_nBLHits;   //!
   TBranch        *b_mu_muid_nPixHits;   //!
   TBranch        *b_mu_muid_nSCTHits;   //!
   TBranch        *b_mu_muid_nTRTHits;   //!
   TBranch        *b_mu_muid_nPixHoles;   //!
   TBranch        *b_mu_muid_nSCTHoles;   //!
   TBranch        *b_mu_muid_nTRTOutliers;   //!
   TBranch        *b_mu_muid_nPixelDeadSensors;   //!
   TBranch        *b_mu_muid_nSCTDeadSensors;   //!
   TBranch        *b_mu_muid_expectBLayerHit;   //!
   TBranch        *b_mu_muid_trackd0pvunbiased;   //!
   TBranch        *b_mu_muid_trackz0pvunbiased;   //!
   TBranch        *b_mu_muid_tracksigd0pvunbiased;   //!
   TBranch        *b_mu_muid_EFCB_index;   //!
   TBranch        *b_mu_staco_n;   //!
   TBranch        *b_mu_staco_E;   //!
   TBranch        *b_mu_staco_pt;   //!
   TBranch        *b_mu_staco_eta;   //!
   TBranch        *b_mu_staco_phi;   //!
   TBranch        *b_mu_staco_charge;   //!
   TBranch        *b_mu_staco_author;   //!
   TBranch        *b_mu_staco_etcone20;   //!
   TBranch        *b_mu_staco_etcone30;   //!
   TBranch        *b_mu_staco_ptcone20;   //!
   TBranch        *b_mu_staco_ptcone30;   //!
   TBranch        *b_mu_staco_isCombinedMuon;   //!
   TBranch        *b_mu_staco_tight;   //!
   TBranch        *b_mu_staco_id_theta_exPV;   //!
   TBranch        *b_mu_staco_id_qoverp_exPV;   //!
   TBranch        *b_mu_staco_me_theta_exPV;   //!
   TBranch        *b_mu_staco_me_qoverp_exPV;   //!
   TBranch        *b_mu_staco_id_d0;   //!
   TBranch        *b_mu_staco_id_z0;   //!
   TBranch        *b_mu_staco_id_phi;   //!
   TBranch        *b_mu_staco_id_theta;   //!
   TBranch        *b_mu_staco_id_qoverp;   //!
   TBranch        *b_mu_staco_nBLHits;   //!
   TBranch        *b_mu_staco_nPixHits;   //!
   TBranch        *b_mu_staco_nSCTHits;   //!
   TBranch        *b_mu_staco_nTRTHits;   //!
   TBranch        *b_mu_staco_nPixHoles;   //!
   TBranch        *b_mu_staco_nSCTHoles;   //!
   TBranch        *b_mu_staco_nTRTOutliers;   //!
   TBranch        *b_mu_staco_nPixelDeadSensors;   //!
   TBranch        *b_mu_staco_nSCTDeadSensors;   //!
   TBranch        *b_mu_staco_expectBLayerHit;   //!
   TBranch        *b_mu_staco_trackd0pvunbiased;   //!
   TBranch        *b_mu_staco_trackz0pvunbiased;   //!
   TBranch        *b_mu_staco_tracksigd0pvunbiased;   //!
   TBranch        *b_mu_staco_EFCB_index;   //!
   TBranch        *b_vxp_n;   //!
   TBranch        *b_vxp_nTracks;   //!
   TBranch        *b_trig_EF_trigmugirl_EF_2mu10_loose;   //!
   TBranch        *b_trig_EF_trigmugirl_EF_mu18_MG;   //!
   TBranch        *b_trig_EF_trigmugirl_track_n;   //!
   TBranch        *b_trig_EF_trigmugirl_track_CB_eta;   //!
   TBranch        *b_trig_EF_trigmugirl_track_CB_phi;   //!
   TBranch        *b_trig_EF_el_n;   //!
   TBranch        *b_trig_EF_el_eta;   //!
   TBranch        *b_trig_EF_el_phi;   //!
   TBranch        *b_trig_EF_el_EF_2e12_medium;   //!
   TBranch        *b_trig_EF_el_EF_e20_medium;   //!
   TBranch        *b_trig_EF_el_EF_e22_medium;   //!

   THiggsD3PD(TTree *tree=0);
   virtual ~THiggsD3PD();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef THiggsD3PD_cxx
THiggsD3PD::THiggsD3PD(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("result.root");
      if (!f) {
         f = new TFile("result.root");
      }
      tree = (TTree*)gDirectory->Get("physics");

   }
   Init(tree);
}

THiggsD3PD::~THiggsD3PD()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t THiggsD3PD::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t THiggsD3PD::LoadTree(Long64_t entry)
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

void THiggsD3PD::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   el_charge = 0;
   el_author = 0;
   el_OQ = 0;
   el_medium = 0;
   el_tight = 0;
   el_loosePP = 0;
   el_Etcone20 = 0;
   el_Etcone30 = 0;
   el_ptcone20 = 0;
   el_ptcone30 = 0;
   el_etap = 0;
   el_etas2 = 0;
   el_cl_E = 0;
   el_cl_pt = 0;
   el_cl_eta = 0;
   el_cl_phi = 0;
   el_trackd0 = 0;
   el_trackz0 = 0;
   el_trackphi = 0;
   el_tracktheta = 0;
   el_trackqoverp = 0;
   el_trackpt = 0;
   el_tracketa = 0;
   el_nPixHits = 0;
   el_nSCTHits = 0;
   el_EF_index = 0;
   el_trackd0pvunbiased = 0;
   el_tracksigd0pvunbiased = 0;
   el_trackz0pvunbiased = 0;
   mu_muid_E = 0;
   mu_muid_pt = 0;
   mu_muid_eta = 0;
   mu_muid_phi = 0;
   mu_muid_charge = 0;
   mu_muid_author = 0;
   mu_muid_etcone20 = 0;
   mu_muid_etcone30 = 0;
   mu_muid_ptcone20 = 0;
   mu_muid_ptcone30 = 0;
   mu_muid_isCombinedMuon = 0;
   mu_muid_tight = 0;
   mu_muid_id_theta_exPV = 0;
   mu_muid_id_qoverp_exPV = 0;
   mu_muid_me_theta_exPV = 0;
   mu_muid_me_qoverp_exPV = 0;
   mu_muid_id_d0 = 0;
   mu_muid_id_z0 = 0;
   mu_muid_id_phi = 0;
   mu_muid_id_theta = 0;
   mu_muid_id_qoverp = 0;
   mu_muid_nBLHits = 0;
   mu_muid_nPixHits = 0;
   mu_muid_nSCTHits = 0;
   mu_muid_nTRTHits = 0;
   mu_muid_nPixHoles = 0;
   mu_muid_nSCTHoles = 0;
   mu_muid_nTRTOutliers = 0;
   mu_muid_nPixelDeadSensors = 0;
   mu_muid_nSCTDeadSensors = 0;
   mu_muid_expectBLayerHit = 0;
   mu_muid_trackd0pvunbiased = 0;
   mu_muid_trackz0pvunbiased = 0;
   mu_muid_tracksigd0pvunbiased = 0;
   mu_muid_EFCB_index = 0;
   mu_staco_E = 0;
   mu_staco_pt = 0;
   mu_staco_eta = 0;
   mu_staco_phi = 0;
   mu_staco_charge = 0;
   mu_staco_author = 0;
   mu_staco_etcone20 = 0;
   mu_staco_etcone30 = 0;
   mu_staco_ptcone20 = 0;
   mu_staco_ptcone30 = 0;
   mu_staco_isCombinedMuon = 0;
   mu_staco_tight = 0;
   mu_staco_id_theta_exPV = 0;
   mu_staco_id_qoverp_exPV = 0;
   mu_staco_me_theta_exPV = 0;
   mu_staco_me_qoverp_exPV = 0;
   mu_staco_id_d0 = 0;
   mu_staco_id_z0 = 0;
   mu_staco_id_phi = 0;
   mu_staco_id_theta = 0;
   mu_staco_id_qoverp = 0;
   mu_staco_nBLHits = 0;
   mu_staco_nPixHits = 0;
   mu_staco_nSCTHits = 0;
   mu_staco_nTRTHits = 0;
   mu_staco_nPixHoles = 0;
   mu_staco_nSCTHoles = 0;
   mu_staco_nTRTOutliers = 0;
   mu_staco_nPixelDeadSensors = 0;
   mu_staco_nSCTDeadSensors = 0;
   mu_staco_expectBLayerHit = 0;
   mu_staco_trackd0pvunbiased = 0;
   mu_staco_trackz0pvunbiased = 0;
   mu_staco_tracksigd0pvunbiased = 0;
   mu_staco_EFCB_index = 0;
   vxp_nTracks = 0;
   trig_EF_trigmugirl_EF_2mu10_loose = 0;
   trig_EF_trigmugirl_EF_mu18_MG = 0;
   trig_EF_trigmugirl_track_n = 0;
   trig_EF_trigmugirl_track_CB_eta = 0;
   trig_EF_trigmugirl_track_CB_phi = 0;
   trig_EF_el_eta = 0;
   trig_EF_el_phi = 0;
   trig_EF_el_EF_2e12_medium = 0;
   trig_EF_el_EF_e20_medium = 0;
   trig_EF_el_EF_e22_medium = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("lbn", &lbn, &b_lbn);
   fChain->SetBranchAddress("actualIntPerXing", &actualIntPerXing, &b_actualIntPerXing);
   fChain->SetBranchAddress("averageIntPerXing", &averageIntPerXing, &b_averageIntPerXing);
   fChain->SetBranchAddress("larError", &larError, &b_larError);
   fChain->SetBranchAddress("EF_2e12_medium", &EF_2e12_medium, &b_EF_2e12_medium);
   fChain->SetBranchAddress("EF_2e12T_medium", &EF_2e12T_medium, &b_EF_2e12T_medium);
   fChain->SetBranchAddress("EF_2e12Tvh_medium", &EF_2e12Tvh_medium, &b_EF_2e12Tvh_medium);
   fChain->SetBranchAddress("EF_2mu10_loose", &EF_2mu10_loose, &b_EF_2mu10_loose);
   fChain->SetBranchAddress("EF_e20_medium", &EF_e20_medium, &b_EF_e20_medium);
   fChain->SetBranchAddress("EF_e22_medium", &EF_e22_medium, &b_EF_e22_medium);
   fChain->SetBranchAddress("EF_e22_medium1", &EF_e22_medium1, &b_EF_e22_medium1);
   fChain->SetBranchAddress("EF_e22vh_medium1", &EF_e22vh_medium1, &b_EF_e22vh_medium1);
   fChain->SetBranchAddress("EF_mu18_MG", &EF_mu18_MG, &b_EF_mu18_MG);
   fChain->SetBranchAddress("EF_mu18_MG_medium", &EF_mu18_MG_medium, &b_EF_mu18_MG_medium);
   fChain->SetBranchAddress("el_GSF_n", &el_n, &b_el_GSF_n);
   fChain->SetBranchAddress("el_GSF_charge", &el_charge, &b_el_GSF_charge);
   fChain->SetBranchAddress("el_GSF_author", &el_author, &b_el_GSF_author);
   fChain->SetBranchAddress("el_GSF_OQ", &el_OQ, &b_el_GSF_OQ);
   fChain->SetBranchAddress("el_GSF_medium", &el_medium, &b_el_GSF_medium);
   fChain->SetBranchAddress("el_GSF_tight", &el_tight, &b_el_GSF_tight);
   fChain->SetBranchAddress("el_GSF_loosePP", &el_loosePP, &b_el_GSF_loosePP);
   fChain->SetBranchAddress("el_GSF_Etcone20", &el_Etcone20, &b_el_GSF_Etcone20);
   fChain->SetBranchAddress("el_GSF_Etcone30", &el_Etcone30, &b_el_GSF_Etcone30);
   fChain->SetBranchAddress("el_GSF_ptcone20", &el_ptcone20, &b_el_GSF_ptcone20);
   fChain->SetBranchAddress("el_GSF_ptcone30", &el_ptcone30, &b_el_GSF_ptcone30);
   fChain->SetBranchAddress("el_GSF_etap", &el_etap, &b_el_GSF_etap);
   fChain->SetBranchAddress("el_GSF_etas2", &el_etas2, &b_el_GSF_etas2);
   fChain->SetBranchAddress("el_GSF_cl_E", &el_cl_E, &b_el_GSF_cl_E);
   fChain->SetBranchAddress("el_GSF_cl_pt", &el_cl_pt, &b_el_GSF_cl_pt);
   fChain->SetBranchAddress("el_GSF_cl_eta", &el_cl_eta, &b_el_GSF_cl_eta);
   fChain->SetBranchAddress("el_GSF_cl_phi", &el_cl_phi, &b_el_GSF_cl_phi);
   fChain->SetBranchAddress("el_GSF_trackd0", &el_trackd0, &b_el_GSF_trackd0);
   fChain->SetBranchAddress("el_GSF_trackz0", &el_trackz0, &b_el_GSF_trackz0);
   fChain->SetBranchAddress("el_GSF_trackphi", &el_trackphi, &b_el_GSF_trackphi);
   fChain->SetBranchAddress("el_GSF_tracktheta", &el_tracktheta, &b_el_GSF_tracktheta);
   fChain->SetBranchAddress("el_GSF_trackqoverp", &el_trackqoverp, &b_el_GSF_trackqoverp);
   fChain->SetBranchAddress("el_GSF_trackpt", &el_trackpt, &b_el_GSF_trackpt);
   fChain->SetBranchAddress("el_GSF_tracketa", &el_tracketa, &b_el_GSF_tracketa);
   fChain->SetBranchAddress("el_GSF_nPixHits", &el_nPixHits, &b_el_GSF_nPixHits);
   fChain->SetBranchAddress("el_GSF_nSCTHits", &el_nSCTHits, &b_el_GSF_nSCTHits);
   fChain->SetBranchAddress("el_GSF_EF_index", &el_EF_index, &b_el_GSF_EF_index);
   fChain->SetBranchAddress("el_GSF_trackd0pvunbiased", &el_trackd0pvunbiased, &b_el_GSF_trackd0pvunbiased);
   fChain->SetBranchAddress("el_GSF_tracksigd0pvunbiased", &el_tracksigd0pvunbiased, &b_el_GSF_tracksigd0pvunbiased);
   fChain->SetBranchAddress("el_GSF_trackz0pvunbiased", &el_trackz0pvunbiased, &b_el_GSF_trackz0pvunbiased);
   fChain->SetBranchAddress("mu_muid_n", &mu_muid_n, &b_mu_muid_n);
   fChain->SetBranchAddress("mu_muid_E", &mu_muid_E, &b_mu_muid_E);
   fChain->SetBranchAddress("mu_muid_pt", &mu_muid_pt, &b_mu_muid_pt);
   fChain->SetBranchAddress("mu_muid_eta", &mu_muid_eta, &b_mu_muid_eta);
   fChain->SetBranchAddress("mu_muid_phi", &mu_muid_phi, &b_mu_muid_phi);
   fChain->SetBranchAddress("mu_muid_charge", &mu_muid_charge, &b_mu_muid_charge);
   fChain->SetBranchAddress("mu_muid_author", &mu_muid_author, &b_mu_muid_author);
   fChain->SetBranchAddress("mu_muid_etcone20", &mu_muid_etcone20, &b_mu_muid_etcone20);
   fChain->SetBranchAddress("mu_muid_etcone30", &mu_muid_etcone30, &b_mu_muid_etcone30);
   fChain->SetBranchAddress("mu_muid_ptcone20", &mu_muid_ptcone20, &b_mu_muid_ptcone20);
   fChain->SetBranchAddress("mu_muid_ptcone30", &mu_muid_ptcone30, &b_mu_muid_ptcone30);
   fChain->SetBranchAddress("mu_muid_isCombinedMuon", &mu_muid_isCombinedMuon, &b_mu_muid_isCombinedMuon);
   fChain->SetBranchAddress("mu_muid_tight", &mu_muid_tight, &b_mu_muid_tight);
   fChain->SetBranchAddress("mu_muid_id_theta_exPV", &mu_muid_id_theta_exPV, &b_mu_muid_id_theta_exPV);
   fChain->SetBranchAddress("mu_muid_id_qoverp_exPV", &mu_muid_id_qoverp_exPV, &b_mu_muid_id_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_me_theta_exPV", &mu_muid_me_theta_exPV, &b_mu_muid_me_theta_exPV);
   fChain->SetBranchAddress("mu_muid_me_qoverp_exPV", &mu_muid_me_qoverp_exPV, &b_mu_muid_me_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_id_d0", &mu_muid_id_d0, &b_mu_muid_id_d0);
   fChain->SetBranchAddress("mu_muid_id_z0", &mu_muid_id_z0, &b_mu_muid_id_z0);
   fChain->SetBranchAddress("mu_muid_id_phi", &mu_muid_id_phi, &b_mu_muid_id_phi);
   fChain->SetBranchAddress("mu_muid_id_theta", &mu_muid_id_theta, &b_mu_muid_id_theta);
   fChain->SetBranchAddress("mu_muid_id_qoverp", &mu_muid_id_qoverp, &b_mu_muid_id_qoverp);
   fChain->SetBranchAddress("mu_muid_nBLHits", &mu_muid_nBLHits, &b_mu_muid_nBLHits);
   fChain->SetBranchAddress("mu_muid_nPixHits", &mu_muid_nPixHits, &b_mu_muid_nPixHits);
   fChain->SetBranchAddress("mu_muid_nSCTHits", &mu_muid_nSCTHits, &b_mu_muid_nSCTHits);
   fChain->SetBranchAddress("mu_muid_nTRTHits", &mu_muid_nTRTHits, &b_mu_muid_nTRTHits);
   fChain->SetBranchAddress("mu_muid_nPixHoles", &mu_muid_nPixHoles, &b_mu_muid_nPixHoles);
   fChain->SetBranchAddress("mu_muid_nSCTHoles", &mu_muid_nSCTHoles, &b_mu_muid_nSCTHoles);
   fChain->SetBranchAddress("mu_muid_nTRTOutliers", &mu_muid_nTRTOutliers, &b_mu_muid_nTRTOutliers);
   fChain->SetBranchAddress("mu_muid_nPixelDeadSensors", &mu_muid_nPixelDeadSensors, &b_mu_muid_nPixelDeadSensors);
   fChain->SetBranchAddress("mu_muid_nSCTDeadSensors", &mu_muid_nSCTDeadSensors, &b_mu_muid_nSCTDeadSensors);
   fChain->SetBranchAddress("mu_muid_expectBLayerHit", &mu_muid_expectBLayerHit, &b_mu_muid_expectBLayerHit);
   fChain->SetBranchAddress("mu_muid_trackd0pvunbiased", &mu_muid_trackd0pvunbiased, &b_mu_muid_trackd0pvunbiased);
   fChain->SetBranchAddress("mu_muid_trackz0pvunbiased", &mu_muid_trackz0pvunbiased, &b_mu_muid_trackz0pvunbiased);
   fChain->SetBranchAddress("mu_muid_tracksigd0pvunbiased", &mu_muid_tracksigd0pvunbiased, &b_mu_muid_tracksigd0pvunbiased);
   fChain->SetBranchAddress("mu_muid_EFCB_index", &mu_muid_EFCB_index, &b_mu_muid_EFCB_index);
   fChain->SetBranchAddress("mu_staco_n", &mu_staco_n, &b_mu_staco_n);
   fChain->SetBranchAddress("mu_staco_E", &mu_staco_E, &b_mu_staco_E);
   fChain->SetBranchAddress("mu_staco_pt", &mu_staco_pt, &b_mu_staco_pt);
   fChain->SetBranchAddress("mu_staco_eta", &mu_staco_eta, &b_mu_staco_eta);
   fChain->SetBranchAddress("mu_staco_phi", &mu_staco_phi, &b_mu_staco_phi);
   fChain->SetBranchAddress("mu_staco_charge", &mu_staco_charge, &b_mu_staco_charge);
   fChain->SetBranchAddress("mu_staco_author", &mu_staco_author, &b_mu_staco_author);
   fChain->SetBranchAddress("mu_staco_etcone20", &mu_staco_etcone20, &b_mu_staco_etcone20);
   fChain->SetBranchAddress("mu_staco_etcone30", &mu_staco_etcone30, &b_mu_staco_etcone30);
   fChain->SetBranchAddress("mu_staco_ptcone20", &mu_staco_ptcone20, &b_mu_staco_ptcone20);
   fChain->SetBranchAddress("mu_staco_ptcone30", &mu_staco_ptcone30, &b_mu_staco_ptcone30);
   fChain->SetBranchAddress("mu_staco_isCombinedMuon", &mu_staco_isCombinedMuon, &b_mu_staco_isCombinedMuon);
   fChain->SetBranchAddress("mu_staco_tight", &mu_staco_tight, &b_mu_staco_tight);
   fChain->SetBranchAddress("mu_staco_id_theta_exPV", &mu_staco_id_theta_exPV, &b_mu_staco_id_theta_exPV);
   fChain->SetBranchAddress("mu_staco_id_qoverp_exPV", &mu_staco_id_qoverp_exPV, &b_mu_staco_id_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_me_theta_exPV", &mu_staco_me_theta_exPV, &b_mu_staco_me_theta_exPV);
   fChain->SetBranchAddress("mu_staco_me_qoverp_exPV", &mu_staco_me_qoverp_exPV, &b_mu_staco_me_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_id_d0", &mu_staco_id_d0, &b_mu_staco_id_d0);
   fChain->SetBranchAddress("mu_staco_id_z0", &mu_staco_id_z0, &b_mu_staco_id_z0);
   fChain->SetBranchAddress("mu_staco_id_phi", &mu_staco_id_phi, &b_mu_staco_id_phi);
   fChain->SetBranchAddress("mu_staco_id_theta", &mu_staco_id_theta, &b_mu_staco_id_theta);
   fChain->SetBranchAddress("mu_staco_id_qoverp", &mu_staco_id_qoverp, &b_mu_staco_id_qoverp);
   fChain->SetBranchAddress("mu_staco_nBLHits", &mu_staco_nBLHits, &b_mu_staco_nBLHits);
   fChain->SetBranchAddress("mu_staco_nPixHits", &mu_staco_nPixHits, &b_mu_staco_nPixHits);
   fChain->SetBranchAddress("mu_staco_nSCTHits", &mu_staco_nSCTHits, &b_mu_staco_nSCTHits);
   fChain->SetBranchAddress("mu_staco_nTRTHits", &mu_staco_nTRTHits, &b_mu_staco_nTRTHits);
   fChain->SetBranchAddress("mu_staco_nPixHoles", &mu_staco_nPixHoles, &b_mu_staco_nPixHoles);
   fChain->SetBranchAddress("mu_staco_nSCTHoles", &mu_staco_nSCTHoles, &b_mu_staco_nSCTHoles);
   fChain->SetBranchAddress("mu_staco_nTRTOutliers", &mu_staco_nTRTOutliers, &b_mu_staco_nTRTOutliers);
   fChain->SetBranchAddress("mu_staco_nPixelDeadSensors", &mu_staco_nPixelDeadSensors, &b_mu_staco_nPixelDeadSensors);
   fChain->SetBranchAddress("mu_staco_nSCTDeadSensors", &mu_staco_nSCTDeadSensors, &b_mu_staco_nSCTDeadSensors);
   fChain->SetBranchAddress("mu_staco_expectBLayerHit", &mu_staco_expectBLayerHit, &b_mu_staco_expectBLayerHit);
   fChain->SetBranchAddress("mu_staco_trackd0pvunbiased", &mu_staco_trackd0pvunbiased, &b_mu_staco_trackd0pvunbiased);
   fChain->SetBranchAddress("mu_staco_trackz0pvunbiased", &mu_staco_trackz0pvunbiased, &b_mu_staco_trackz0pvunbiased);
   fChain->SetBranchAddress("mu_staco_tracksigd0pvunbiased", &mu_staco_tracksigd0pvunbiased, &b_mu_staco_tracksigd0pvunbiased);
   fChain->SetBranchAddress("mu_staco_EFCB_index", &mu_staco_EFCB_index, &b_mu_staco_EFCB_index);
   fChain->SetBranchAddress("vxp_n", &vxp_n, &b_vxp_n);
   fChain->SetBranchAddress("vxp_nTracks", &vxp_nTracks, &b_vxp_nTracks);
   fChain->SetBranchAddress("trig_EF_trigmugirl_EF_2mu10_loose", &trig_EF_trigmugirl_EF_2mu10_loose, &b_trig_EF_trigmugirl_EF_2mu10_loose);
   fChain->SetBranchAddress("trig_EF_trigmugirl_EF_mu18_MG", &trig_EF_trigmugirl_EF_mu18_MG, &b_trig_EF_trigmugirl_EF_mu18_MG);
   fChain->SetBranchAddress("trig_EF_trigmugirl_track_n", &trig_EF_trigmugirl_track_n, &b_trig_EF_trigmugirl_track_n);
   fChain->SetBranchAddress("trig_EF_trigmugirl_track_CB_eta", &trig_EF_trigmugirl_track_CB_eta, &b_trig_EF_trigmugirl_track_CB_eta);
   fChain->SetBranchAddress("trig_EF_trigmugirl_track_CB_phi", &trig_EF_trigmugirl_track_CB_phi, &b_trig_EF_trigmugirl_track_CB_phi);
   fChain->SetBranchAddress("trig_EF_el_n", &trig_EF_el_n, &b_trig_EF_el_n);
   fChain->SetBranchAddress("trig_EF_el_eta", &trig_EF_el_eta, &b_trig_EF_el_eta);
   fChain->SetBranchAddress("trig_EF_el_phi", &trig_EF_el_phi, &b_trig_EF_el_phi);
   fChain->SetBranchAddress("trig_EF_el_EF_2e12_medium", &trig_EF_el_EF_2e12_medium, &b_trig_EF_el_EF_2e12_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_e20_medium", &trig_EF_el_EF_e20_medium, &b_trig_EF_el_EF_e20_medium);
   fChain->SetBranchAddress("trig_EF_el_EF_e22_medium", &trig_EF_el_EF_e22_medium, &b_trig_EF_el_EF_e22_medium);
   Notify();
}

Bool_t THiggsD3PD::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void THiggsD3PD::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t THiggsD3PD::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef THiggsD3PD_cxx
