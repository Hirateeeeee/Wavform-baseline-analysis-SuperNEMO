
#include "TStyle.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include <iostream>
#include <memory>
#define _USE_MATH_DEFINES
#include <fstream>
#include <sstream>
#include <vector>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TF1.h>
#include <TStyle.h>
#include "TKey.h"
#include "TFile.h"
#include "TTree.h"
#include "TLine.h"
#include "TROOT.h"
#include <TText.h>
#include <TLatex.h>
#include <TRandom3.h>
#include <TLegend.h>
#include <TSystem.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <TParameter.h>
#include <numeric>
#include <cstdlib>

int calo_track_corresponder(int calo_column, int track_layer){
  if (calo_column == 0 && track_layer >= 0 && track_layer <= 6) return 1;
  if (calo_column == 1 && track_layer >= 2 && track_layer <= 11) return 1;
  if (calo_column == 2 && track_layer >= 8 && track_layer <= 17) return 1;
  if (calo_column == 3 && track_layer >= 14 && track_layer <= 24) return 1;
  if (calo_column == 4 && track_layer >= 19 && track_layer <= 29) return 1;
  if (calo_column == 5 && track_layer >= 25 && track_layer <= 34) return 1;
  if (calo_column == 6 && track_layer >= 31 && track_layer <= 40) return 1;
  if (calo_column == 7 && track_layer >= 37 && track_layer <= 46) return 1;
  if (calo_column == 8 && track_layer >= 43 && track_layer <= 52) return 1;
  if (calo_column == 9 && track_layer >= 49 && track_layer <= 58) return 1;
  if (calo_column == 10 && track_layer >= 55 && track_layer <= 64) return 1;
  if (calo_column == 11 && track_layer >= 61 && track_layer <= 70) return 1;
  if (calo_column == 12 && track_layer >= 66 && track_layer <= 75) return 1;
  if (calo_column == 13 && track_layer >= 72 && track_layer <= 81) return 1;
  if (calo_column == 14 && track_layer >= 78 && track_layer <= 87) return 1;
  if (calo_column == 15 && track_layer >= 84 && track_layer <= 93) return 1;
  if (calo_column == 16 && track_layer >= 90 && track_layer <= 99) return 1;
  if (calo_column == 17 && track_layer >= 96 && track_layer <= 105) return 1;
  if (calo_column == 18 && track_layer >= 101 && track_layer <= 110) return 1;
  if (calo_column == 19 && track_layer >= 107 && track_layer <= 112) return 1;
  else return 0;
}



int main() {
 gStyle->SetOptStat(0);
  TFile *file = new TFile("/sps/nemo/scratch/pli/aussois_tuto_data/bi207_run/snemo_run-902_udd.root", "READ");
  std::vector<std::vector<short>> *wave = new std::vector<std::vector<short>>;
  std::vector<int> *calo_wall   = new std::vector<int>;
  std::vector<int> *calo_side   = new std::vector<int>;
  std::vector<int> *calo_column = new std::vector<int>;
  std::vector<int> *calo_row    = new std::vector<int>;
  std::vector<int> *calo_charge = new std::vector<int>;
  std::vector<int> *calo_ampl   = new std::vector<int>;
  std::vector<int> *tracker_side   = new std::vector<int>;
  std::vector<int> *tracker_column = new std::vector<int>;
  std::vector<int> *tracker_row    = new std::vector<int>;
  std::vector<int> *tracker_layer  = new std::vector<int>;

  int ncalo_main_wall = 520;
  int counter = 0;

  int eventnumber = 0;
  int calo_nohits = 0;
  int tracker_nohits = 0;

  TTree* tree = (TTree*)file->Get("SimData");
  
  //TTree* originalTree = (TTree*)file->Get("SimData");
  //gROOT->cd();
  //TTree* temptree = originalTree->CopyTree("digicalo.charge@->size()>0", "" , 900000 );
  //TTree* tree = temptree->CopyTree("digicalo.charge@->size()>0 && digicalo.charge@->at(0) < 25000 && digicalo.charge@->at(0) > 24000");
  
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("header.eventnumber",1);
  tree->SetBranchAddress("header.eventnumber", &eventnumber);
  tree->SetBranchStatus("digicalo.nohits",1);
  tree->SetBranchAddress("digicalo.nohits", &calo_nohits);
  tree->SetBranchStatus("digicalo.waveform",1);
  tree->SetBranchAddress("digicalo.waveform", &wave);
  tree->SetBranchStatus("digicalo.wall",1);
  tree->SetBranchAddress("digicalo.wall", &calo_wall);
  tree->SetBranchStatus("digicalo.side",1);
  tree->SetBranchAddress("digicalo.side", &calo_side);
  tree->SetBranchStatus("digicalo.column",1);
  tree->SetBranchAddress("digicalo.column", &calo_column);
  tree->SetBranchStatus("digicalo.row",1);
  tree->SetBranchAddress("digicalo.row", &calo_row);
  tree->SetBranchStatus("digicalo.charge",1);
  tree->SetBranchAddress("digicalo.charge", &calo_charge)
  tree->SetBranchStatus("digicalo.peakamplitude",1);
  tree->SetBranchAddress("digicalo.peakamplitude", &calo_ampl);
  /*
  tree->SetBranchStatus("digitracker.nohits",1);
  tree->SetBranchAddress("digitracker.nohits", &tracker_nohits);
  tree->SetBranchStatus("digitracker.side",1);
  tree->SetBranchAddress("digitracker.side", &tracker_side);
  tree->SetBranchStatus("digitracker.layer",1);
  tree->SetBranchAddress("digitracker.layer", &tracker_layer);
  tree->SetBranchStatus("digitracker.column",1);
  tree->SetBranchAddress("digitracker.column", &tracker_column);
  */
  TH2D calo_full("calo_full","calo_full", 24, -2, 22, 32, -16, 16);
  TH2D calo("calo","calo", 24, -2, 22, 32, -16, 16);
  TH1D *waveform = new TH1D("waveform","eventnumber18232 (baseline = 6blocks sample 0-95)", 1024, 0, 1024);
  TH1D *reference = new TH1D("ref","ref", 1024, 0, 1024);
  TH1D *waveform_compare = new TH1D("waveform compare","waveform compare (event = 300000 baseline = 6 block (32-127))",1000,0,1000);
  TH1D *waveform_difference = new TH1D("waveform subtraction","waveform subtraction (event = 5000, baseline = 6 block)",2000,0,2000);
  TH2D *waveform_2D = new TH2D("waveform","waveform (event = 300000, baseline = 6 blocks (32-127))",100,0,30000,100,0,30000);
  TH2D *x_y = new TH2D("x=y","x=y",1000,0,30000,1000,0,30000);


  for (int z=0; z <30000; z++)    ## this draw a diagonal line of x=y on the diagram
  {
    int x = z;
    int y = z;
    x_y -> Fill(x,y);

  } 


  for (int i = 0; i < tree->GetEntries() - 1; i++) {    // this take in data in a event loop, and output a message once it take in integer mutiple of 100 events
    tree->GetEntry(i);
    
    if (i%100==0) std::cout<<"Event "<<i<<std::endl;
    if(wave->size()<2) 
      {
        std::cout<<"Skipping event "<<i<<std::endl;    // this ensure any broken event with incomplete waveform data get deleted before any analysis happening, prevent error
        continue;
      }
  
    for (int l=0; l < wave->at(1).size();l++){    //this manually calculate the waveform base line
      std::vector<int> samples;
      
      int ave;


      for (int k=32; k<127; k++){ //## to change the blocks you need for calculating the baseline, change the number here
        samples.insert(samples.end(),wave->at(1).at(k)); //## for example, 32 and 127 here means it take average between 32(block 2) and 127(block 9)
        int sum = accumulate(samples.begin(),samples.end(),0);
        ave = sum/samples.size();
        
        
        
      }

      
      waveform -> SetBinContent(l, wave->at(1).at(l)); //##set both the wave and the manually calculated baseline into the graph
      reference -> SetBinContent(l,ave);

      
    
    }
  
  int waveform_integral = reference -> Integral() - waveform -> Integral(); #integral to get the area under the waveform
  //double fraction = calo_charge->at(1)/waveform_integral;
  double subtract = -1 * calo_charge->at(1) - waveform_integral;
  
  
  if ( abs(waveform_integral) < 2500 && abs(calo_charge->at(1)) < 2500)   //##filter out the trivial events where nothing is happening
  {
  //std::cout<<"small event"<<i<<std::endl;
  continue;
  
  
  }

  if ( abs(waveform_integral) - abs(calo_charge->at(1)) == 0)  //## find the events that have manually baseline exactly equal to the automatically calculated baseline
  {
    std::cout << "equal event" << i << std::endl;
    continue;
  }

  if ( abs(waveform_integral) - abs(calo_charge->at(1)) > 1000) //## find the event that have a large difference bewteen the manual calculation and automatic calculation
  {
    std::cout << "manual intergral greater than FEB with more than 1000" << i << std::endl;
    std::cout << "difference is " << abs(waveform_integral) - abs(calo_charge->at(1)) << std::endl;
    continue;
  }

  if (abs(waveform_integral) == 10000)
  {
    std::cout<< "manual integral = 1000 at event " << i << "with FEB " << calo_charge->at(1) <<  std::endl;
    continue;
  }




  //waveform_compare -> SetBinContent(i,fraction);
  waveform_difference -> SetBinContent(i,subtract);
  waveform_2D -> Fill(-1*calo_charge->at(1),waveform_integral);



 //######create canvas and print everything out####
  //std::cout << "--------- event number " << i << "---------" << std::endl; 
/*
  std::cout << "Calo charge: " << calo_charge->at(1) << std::endl; 
  std::cout << "Integal of waveform is: " <<  waveform -> Integral() << std::endl;  
  std::cout << "Integal of reference is: " << reference -> Integral() << std::endl;
  std::cout << "The difference is: " << reference -> Integral() - waveform -> Integral() << std::endl;
  std::cout << "The waveform integral is: " << waveform_integral << std::endl;
  std::cout << "The difference between manual calculate and FEB calculate is :" << subtract << std::endl;
  std::cout << "--------------------------------------" << std::endl;
*/
  
  TFile *newfile_2 = new TFile("output_from_macro.root", "RECREATE");
  newfile_2->cd();
  waveform->Write();
  reference->Write();
  waveform_compare->Write();
  newfile_2->Close();
  //std::cout << "End of macro.C" << std::endl;
  } 
  TCanvas *canv_2=new TCanvas("canv_2","Elvis's plot",900,600);
  waveform_2D -> Draw("colz");
  x_y-> Draw("same");
  TCanvas *canv_3=new TCanvas("canv_3","Elvis's plot",900,600);
  waveform_difference -> Draw("colz");
  waveform_difference->GetYaxis()->SetRangeUser(-10000,10000);
  
  TCanvas *canv_4 = new TCanvas("canv_4","Elvis's plot",900,600);
  waveform_compare -> Draw();
  waveform_compare -> GetYaxis()->SetRangeUser(-20,20);


  canv_2->SaveAs("waveform2D.png");
  canv_3->SaveAs("subtraction.png");
  //canv_4->SaveAs("compare.png");
  

  return 0;


/*    //### below are the code for retrieve information from a single event
  tree->GetEntry(18183); ## change the event number here to get information from the event of your interest
  int ave;
  double chi_square;
  

    
    for (int l=0; l < wave->at(1).size();l++){

    //int sample1, sample2, sample3, sample4, sample5, sample6, sample7, sample8, sample9,
    //sample10, sample11, sample12, sample13, sample14, sample15, sample16;
    
    //sample1 = wave->at(1).at(1);
    //sample2 = wave->at(1).at(2);
    //sample3 = wave->at(1).at(3);
    //sample4 = wave->at(1).at(4);
    //sample5 = wave->at(1).at(5);
    //sample6 = wave->at(1).at(6);
    //sample7 = wave->at(1).at(7);
    //sample8 = wave->at(1).at(8);
    //sample9 = wave->at(1).at(9);
    //sample10 = wave->at(1).at(10);
    //sample11 = wave->at(1).at(11);
    //sample12 = wave->at(1).at(12);
    //sample13 = wave->at(1).at(13);
    //sample14 = wave->at(1).at(14);
    //sample15 = wave->at(1).at(15);
    //sample16 = wave->at(1).at(16);

    //int ave = (sample1 + sample2 + sample3 + sample4 + sample5 + sample6
    //+ sample7 + sample8+ sample9 + sample10 + sample11 + sample12 + sample13 + sample14 + sample15
    //+ sample16)/16;
    std::vector<int> samples;
    std::vector<double> chi_square_list;
    
    
    
    

      for (int k=0; k<95; k++){
        samples.insert(samples.end(),wave->at(1).at(k));
        int sum = accumulate(samples.begin(),samples.end(),0);
        ave = sum/samples.size();
        
        
      }


    waveform -> SetBinContent(l, wave->at(1).at(l));
    reference -> SetBinContent(l,ave);

      for (int chi = 0; chi<95; chi++){
        double observe_subtract_expect = wave->at(1).at(chi)-ave;
        
        
        double chi_square_value = pow(observe_subtract_expect,2)/ave;

        
        chi_square_list.insert(chi_square_list.end(),chi_square_value);

        
      


      }

      
      chi_square = accumulate(chi_square_list.begin(),chi_square_list.end(),0.0);
      
      
    
    
    }
  
  TCanvas *canv=new TCanvas("canv","Elvis's plot",900,600); ## output everything and calculate chi square
  waveform->GetYaxis()->SetRangeUser(3000,3700);
  waveform -> Draw();
  reference -> Draw("same");
  canv->SaveAs("0-95.png");
  std::cout << "--------- event number " << i << "---------" << std::endl;
  std::cout << "Integal of waveform is: " <<  waveform -> Integral() << std::endl;
  std::cout << "Integal of reference is: " << reference -> Integral() << std::endl;
  std::cout << "The difference is: " << reference -> Integral() - waveform -> Integral() << std::endl;
  std::cout << "The calo_charge is: " << -1*calo_charge->at(1) << std::endl;
  std::cout<<"chi square value is: "<<chi_square<<std::endl;
  std::cout << "ave is " << ave << std::endl;
  std::cout << "------------------" << std::endl;
  TFile *newfile_2 = new TFile("output_from_macro.root", "RECREATE");
  newfile_2->cd();
  waveform->Write();
  reference->Write();
  newfile_2->Close();
  //std::cout << "End of macro.C" << std::endl;
  




/* //## same code to extract a singular event
  tree->GetEntry(18232);
  int ave;
  double chi_square;
  

    
    for (int l=0; l < wave->at(1).size();l++){

    //int sample1, sample2, sample3, sample4, sample5, sample6, sample7, sample8, sample9,
    //sample10, sample11, sample12, sample13, sample14, sample15, sample16;
    
    //sample1 = wave->at(1).at(1);
    //sample2 = wave->at(1).at(2);
    //sample3 = wave->at(1).at(3);
    //sample4 = wave->at(1).at(4);
    //sample5 = wave->at(1).at(5);
    //sample6 = wave->at(1).at(6);
    //sample7 = wave->at(1).at(7);
    //sample8 = wave->at(1).at(8);
    //sample9 = wave->at(1).at(9);
    //sample10 = wave->at(1).at(10);
    //sample11 = wave->at(1).at(11);
    //sample12 = wave->at(1).at(12);
    //sample13 = wave->at(1).at(13);
    //sample14 = wave->at(1).at(14);
    //sample15 = wave->at(1).at(15);
    //sample16 = wave->at(1).at(16);

    //int ave = (sample1 + sample2 + sample3 + sample4 + sample5 + sample6
    //+ sample7 + sample8+ sample9 + sample10 + sample11 + sample12 + sample13 + sample14 + sample15
    //+ sample16)/16;
    std::vector<int> samples;
    std::vector<double> chi_square_list;
    
    
    
    

      for (int k=32; k<127; k++){
        samples.insert(samples.end(),wave->at(1).at(k));
        int sum = accumulate(samples.begin(),samples.end(),0);
        ave = sum/samples.size();
        
        
      }


    waveform -> SetBinContent(l, wave->at(1).at(l));
    reference -> SetBinContent(l,ave);

      for (int chi = 32; chi<127; chi++){
        double observe_subtract_expect = wave->at(1).at(chi)-ave;
        
        
        double chi_square_value = pow(observe_subtract_expect,2)/ave;

        
        chi_square_list.insert(chi_square_list.end(),chi_square_value);

        
      


      }

      
      chi_square = accumulate(chi_square_list.begin(),chi_square_list.end(),0.0);
      
      
    
    
    }
  
  TCanvas *canv=new TCanvas("canv","Elvis's plot",900,600);
  waveform->GetYaxis()->SetRangeUser(3000,3700);
  waveform -> Draw();
  reference -> Draw("same");
  canv->SaveAs("32-127.png");
  std::cout << "--------- event number " << i (32-127)<< "---------" << std::endl;
  std::cout << "Integal of waveform is: " <<  waveform -> Integral() << std::endl;
  std::cout << "Integal of reference is: " << reference -> Integral() << std::endl;
  std::cout << "The difference is: " << reference -> Integral() - waveform -> Integral() << std::endl;
  std::cout << "The calo_charge is: " << -1*calo_charge->at(1) << std::endl;
  std::cout<<"chi square value is: "<<chi_square<<std::endl;
  std::cout << "ave is " << ave << std::endl;
  
  std::cout << "------------------" << std::endl;
  TFile *newfile_2 = new TFile("output_from_macro.root", "RECREATE");
  newfile_2->cd();
  waveform->Write();
  reference->Write();
  newfile_2->Close();

  return 0;

*/

}












