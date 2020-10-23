#include <stdio.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TH2D.h>
#include "TF1.h"
#include <string.h>
#include "TLatex.h"
#include <TTree.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <TGraphErrors.h>
#include <TFile.h>
#include "TLatex.h"
#include "TVector3.h"

using namespace std;


int main() {
    std::string fileName = "/Users/Mariangela/work/streaming/simul/macro/out.root";
    TFile *f1 = new TFile(fileName.c_str(), "Read");
    
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetCanvasColor(10);

    gStyle->SetPadBorderMode(0);
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadRightMargin(0.12);
    gStyle->SetPadColor(10);


    gStyle->SetTitleFont(72,"X");
    gStyle->SetTitleFont(72,"Y");
    gStyle->SetTitleOffset(0.9,"X");
    gStyle->SetTitleOffset(1.2,"Y");
    gStyle->SetTitleSize(0.05,"X");
    gStyle->SetTitleSize(0.05,"Y");
    
    gStyle->SetLabelFont(72,"X");
    gStyle->SetLabelFont(72,"Y");
    gStyle->SetLabelFont(72,"Z");
//    gStyle->SetOptFit(111);
  //  gStyle->SetOptStat("nemriou");
   // gStyle->SetOptStat("");

    gStyle->SetPalette(1);

    // generated
    int   ngen;
    vector<double>  *pid_gen = new vector<double>;
    vector<double>   *px_gen = 0;
    vector<double>   *py_gen = 0;
    vector<double>   *pz_gen = 0;
    
    vector<double>   *vx_gen = 0;
    vector<double>   *vy_gen = 0;
    vector<double>   *vz_gen = 0;
    
    
    // flux
    const int NDCHITMAX = 100000;
    int   ndchit;
    vector<double>   *id = 0;

    vector<double>   *px = 0;
    vector<double>   *py = 0;
    vector<double>   *pz = 0;
    
    vector<double>   *pid= 0;
    vector<double>   *vx = 0;
    vector<double>   *vy = 0;
    vector<double>   *vz = 0;
    
    vector<double> *mpid = 0;
    vector<double>  *mvx = 0;
    vector<double>  *mvy = 0;
    vector<double>  *mvz = 0;
	

    
    // GENERATED
        TTree *g = (TTree *) f1->Get("generated");
 //   TChain *g= new TChain("generated");
   // g->Add("out*.root");
    g->SetBranchAddress("pid",&pid_gen);
    g->SetBranchAddress("vx",&vx_gen);
    g->SetBranchAddress("vy",&vy_gen);
    g->SetBranchAddress("vz",&vz_gen);
    g->SetBranchAddress("px",&px_gen);
    g->SetBranchAddress("py",&py_gen);
    g->SetBranchAddress("pz",&pz_gen);
    
    // flux
    TTree *d = (TTree *) f1->Get("flux");
 //   TChain *d= new TChain("flux");
  //  d->Add("out*.root");
    //    d->SetBranchAddress("ndchit",&ndchit);
    d->SetBranchAddress("id",&id);
    d->SetBranchAddress("mpid",&mpid);
    d->SetBranchAddress("mvx",&mvx);
    d->SetBranchAddress("mvy",&mvy);
    d->SetBranchAddress("mvz",&mvz);
    d->SetBranchAddress("pid",&pid);
    d->SetBranchAddress("vx",&vx);
    d->SetBranchAddress("vy",&vy);
    d->SetBranchAddress("vz",&vz);
    d->SetBranchAddress("px",&px);
    d->SetBranchAddress("py",&py);
    d->SetBranchAddress("pz",&pz);
    
    Long64_t nentries = d->GetEntries();
    cout << "Number of entres: "<<nentries << endl;

     //Histo flux generated
    
    TH1D *h_Z_gen = new TH1D(Form("h_Z_gen"), Form("h_Z_gen"),200, -1000.,1000);
    h_Z_gen->GetXaxis()->SetTitle("z[mm] ");
    h_Z_gen->SetTitle("Z generated");
    
    TH1D *h_p_gen = new TH1D(Form("h_p_gen"), Form("h_p_gen"),300, 900.,9000);
    h_p_gen->GetXaxis()->SetTitle("p[MeV] ");
    h_p_gen->SetTitle("p generated");
    
    TH1D *h_theta_gen = new TH1D(Form("h_theta_gen"), Form("h_theta_gen"),200, -0.5,20.);
    h_theta_gen->GetXaxis()->SetTitle("theta[deg] ");
    h_theta_gen->SetTitle("theta generated");
    
    

    //Histo flux target
    
    TH1D *h_Nhit_flux_target = new TH1D(Form("h_Nhit_flux_target"), Form("h_Nhit_flux_target"),20, -0.5,20.5);
    h_Nhit_flux_target->GetXaxis()->SetTitle("Nhit ");
    h_Nhit_flux_target->SetTitle("Nhit flux det. target");
    
    TH1D *h_Egamma_flux_target = new TH1D(Form("h_Egamma_flux_target"), Form("h_Egamma_flux_target"),100, 0.,8000.);
    h_Egamma_flux_target->GetXaxis()->SetTitle("E[MeV]");
    h_Egamma_flux_target->SetTitle("Gamma energy flux det. target");
    
    TH1D *h_angleg1g2_flux_target = new TH1D(Form("h_angleg1g2_flux_target"), Form("h_angleg1g2_flux_target"),100, -0.5,30.);
    h_angleg1g2_flux_target->GetXaxis()->SetTitle("theta[deg]");
    h_angleg1g2_flux_target->SetTitle("theta g1 g2 flux det. target");
    
    TH1D *h_mass_flux_target = new TH1D(Form("h_mass_flux_target"), Form("h_mass_flux_target"),200, 40.,200);
    h_mass_flux_target->GetXaxis()->SetTitle("mass[MeV]");
    h_mass_flux_target->SetTitle("Mass pi0 flux det. target");
    
    
     //Histo flux ft
    
    TH1D *h_Nhit_flux_ft = new TH1D(Form("h_Nhit_flux_ft"), Form("h_Nhit_flux_ft"),20, -0.5,20.5);
    h_Nhit_flux_ft->GetXaxis()->SetTitle("Nhit ");
    h_Nhit_flux_ft->SetTitle("Nhit flux det. ft");
    
    TH1D *h_Nhit_flux_ft_th = new TH1D(Form("h_Nhit_flux_ft_th"), Form("h_Nhit_flux_ft_th"),20, -0.5,20.5);
    h_Nhit_flux_ft_th->GetXaxis()->SetTitle("Nhit ");
    h_Nhit_flux_ft_th->SetTitle("Nhit flux det. ft Energy thr >100 MeV)");
    
    TH1D *h_Egamma_flux_ft = new TH1D(Form("h_Egamma_flux_ft"), Form("h_Egamma_flux_ft"),100, 0.,8000.);
    h_Egamma_flux_ft->GetXaxis()->SetTitle("E[MeV]");
    h_Egamma_flux_ft->SetTitle("Gamma energy flux det. ft");
    
    TH1D *h_angleg1g2_flux_ft = new TH1D(Form("h_angleg1g2_flux_ft"), Form("h_angleg1g2_flux_ft"),100, -0.5,30.);
    h_angleg1g2_flux_ft->GetXaxis()->SetTitle("theta[deg]");
    h_angleg1g2_flux_ft->SetTitle("theta g1 g2 flux det. ft)");
    
    TH1D *h_mass_flux_ft = new TH1D(Form("h_mass_flux_ft"), Form("h_mass_flux_ft"),200, 40.,200);
    h_mass_flux_ft->GetXaxis()->SetTitle("mass[MeV]");
    h_mass_flux_ft->SetTitle("Mass pi0 flux det. ft");
    
    
    TH2D *h_Egamma_Epi0_ft = new TH2D(Form("h_Egamma_Epi0_ft"), Form("h_Egamma_Epi0_ft"),100, 0., 8000,100, 0.,8000.);
    h_Egamma_Epi0_ft->GetXaxis()->SetTitle("Epi0[MeV]");
    h_Egamma_Epi0_ft->GetYaxis()->SetTitle("Egammas[MeV]");
    h_Egamma_Epi0_ft->SetTitle("Egammas vs Epio  ft");
    
/*
    TH1F *hi_bg_z_reg[3];
    for(int i=0; i<3; i++) {
   
    hi_bg_z_reg[i]= new TH1F(Form("hi_bg_z_region%i",i+1), Form("hi_bg_z_region%i",i+1),100, -200.,6500.);
	hi_bg_z_reg[i]->GetXaxis()->SetTitle("z(mm)");
	hi_bg_z_reg[i]->SetTitle("Rate (MHz)");
        
    }
    TH2F *hi_bg_y_vs_x_Vz100reg[3];
    for(int i=0; i<3; i++) {
    hi_bg_y_vs_x_Vz100reg[i]= new TH2F(Form("hi_bg_y_vs_x_Vz100reg%i",i+1), Form("hi_bg_y_vs_x_Vz100reg%i",i+1),100, -1.,1., 100, -1.,1.);
    hi_bg_y_vs_x_Vz100reg[i]->GetXaxis()->SetTitle("x(mm)");
    hi_bg_y_vs_x_Vz100reg[i]->GetYaxis()->SetTitle("y(mm)");
    }
*/
    int nint=0;
    int ngoodentries=0;
    int ntheta=0;
    int N_event_fluxtarget_good=0;
    int N_event_fluxft_good=0;
    int flag_mass_ft_ok=0;
    double Epi0=0;

   
    
    for(int j=0; j < nentries; j++) {
        

        flag_mass_ft_ok=0;
        int Nhit_flux_target=0;
        double E_gamma_flux_target[4];
        double pid_flux_target[4];
        for(int i=0; i<4; i++){
            E_gamma_flux_target[i]=0;
            pid_flux_target[i]=0;
        }
        double theta_flux_target=0;
        double mass_flux_target=0;
        TVector3 v_flux_target[4];
        TVector3 v_gen;
        TVector3 v_flux_ft_dummy;
        int Nhit_flux_ft=0;
        int Nhit_flux_ft_th=0;
        
        vector<double> *E_gamma_flux_ft = new vector<double>;
        vector<double> *pid_flux_ft = new vector<double>;
         vector<TVector3> *v_flux_ft = new vector<TVector3>;
        double theta_flux_ft=0;
        double mass_flux_ft=0;
 
        pid_gen->clear();
        id->clear();

        px->clear();
        py->clear();
        pz->clear();
        
        vx->clear();
        vy->clear();
        vz->clear();
        
        mpid->clear();
        mvx->clear();
        mvy->clear();
        mvz->clear();
        
        d->GetEntry(j);
        g->GetEntry(j);
        ngen=pid_gen->size();
   
        if(ngen>0) {
          //  cout <<ngen<<" "<<j<<endl;
        
            ngoodentries++;
             Epi0 = sqrt(px_gen->at(0)*px_gen->at(0)+ py_gen->at(0)*py_gen->at(0) +pz_gen->at(0)*pz_gen->at(0));
            //fill histo generated
            
            v_gen.SetXYZ(px_gen->at(0),py_gen->at(0),pz_gen->at(0));
            h_Z_gen->Fill(vz_gen->at(0));
            h_p_gen->Fill(sqrt(px_gen->at(0)*px_gen->at(0)+ py_gen->at(0)*py_gen->at(0) +pz_gen->at(0)*pz_gen->at(0)));
        //    cout <<sqrt(px_gen->at(0)*px_gen->at(0)+ py_gen->at(0)*py_gen->at(0) +pz_gen->at(0)*pz_gen->at(0))<<endl;
            h_theta_gen->Fill(v_gen.Theta()*180/3.1415);
            if((v_gen.Theta()*180/3.1415)<5) ntheta=ntheta+1;
 
         //   cout <<"NEW event "<<endl;
            for(int p=0; p < id->size(); p++) {
                                
                if(id->at(p)==1){
                    if(mpid->at(p)==111){
                        Nhit_flux_target +=1;
                        pid_flux_target[Nhit_flux_target-1] = pid->at(p);
                        E_gamma_flux_target[Nhit_flux_target-1] = sqrt(px->at(p)*px->at(p) + py->at(p)*py->at(p) +pz->at(p)*pz->at(p));
                        h_Egamma_flux_target->Fill(E_gamma_flux_target[Nhit_flux_target-1]);
                        v_flux_target[Nhit_flux_target-1].SetXYZ(px->at(p),py->at(p),pz->at(p));
                 
                }
                }
                
                
                if(id->at(p)==2){
                     Nhit_flux_ft++;
                    
                    pid_flux_ft->push_back(pid->at(p));
                    h_Egamma_flux_ft->Fill(sqrt(px->at(p)*px->at(p) + py->at(p)*py->at(p) +pz->at(p)*pz->at(p)));
                    if((sqrt(px->at(p)*px->at(p) + py->at(p)*py->at(p) +pz->at(p)*pz->at(p)))>500 && pid->at(p)==22) {
                        E_gamma_flux_ft->push_back(sqrt(px->at(p)*px->at(p) + py->at(p)*py->at(p) +pz->at(p)*pz->at(p)));
                        //cout <<sqrt(px->at(p)*px->at(p) + py->at(p)*py->at(p) +pz->at(p)*pz->at(p))<<endl;
                        Nhit_flux_ft_th+=1;
                      //  cout <<Nhit_flux_ft_th<<endl;
                        v_flux_ft_dummy.SetXYZ(px->at(p),py->at(p),pz->at(p));
                        v_flux_ft->push_back(v_flux_ft_dummy);
                        
                    }
                    
                }//end flux 1
             
               
            } //end for
            
            
            if(Nhit_flux_target==2 && pid_flux_target[0]==22&& pid_flux_target[1]==22){
                
             theta_flux_target=  v_flux_target[0].Angle(v_flux_target[1]);
                h_angleg1g2_flux_target->Fill(theta_flux_target*180/3.1415);
             mass_flux_target = sqrt(2*E_gamma_flux_target[0]*E_gamma_flux_target[1]*(1-cos(theta_flux_target)));
                h_mass_flux_target->Fill(mass_flux_target);
               
                
            }
            

            if(Nhit_flux_ft_th>1 ){
                
                for(int v=1; v<Nhit_flux_ft_th;v++){
                    cout << v_flux_ft->at(0).X()<<" "<<v_flux_ft->at(0).Y()<<" "<<v_flux_ft->at(0).Z()<<" "<<E_gamma_flux_ft->at(0)<<endl;
                     cout << v_flux_ft->at(v).X()<<" "<<v_flux_ft->at(v).Y()<<" "<<v_flux_ft->at(v).Z()<<" "<<E_gamma_flux_ft->at(v)<<endl;
                    theta_flux_ft=  v_flux_ft->at(0).Angle(v_flux_ft->at(v));
                    cout <<"THETA ft"<<" "<<theta_flux_ft<<endl;
                    h_angleg1g2_flux_ft->Fill(theta_flux_ft*180/3.1415);
                    mass_flux_ft = sqrt(2*E_gamma_flux_ft->at(0)*E_gamma_flux_ft->at(v)*(1-cos(theta_flux_ft)));
                    cout <<"mass ft"<<" "<<mass_flux_ft<<endl;
                    h_mass_flux_ft->Fill(mass_flux_ft);
                    if(mass_flux_ft>134&&mass_flux_ft<136){
                        
                
                        flag_mass_ft_ok=1;
                        h_Egamma_Epi0_ft->Fill(Epi0 ,E_gamma_flux_ft->at(0));
                          h_Egamma_Epi0_ft->Fill(Epi0 , E_gamma_flux_ft->at(v));
                }
                        }
            
            }
            
            h_Nhit_flux_target->Fill(Nhit_flux_target);
            h_Nhit_flux_ft->Fill(Nhit_flux_ft);
            h_Nhit_flux_ft_th->Fill(Nhit_flux_ft_th);
            
            
            if(Nhit_flux_target>0) N_event_fluxtarget_good++;
            if(flag_mass_ft_ok==1) N_event_fluxft_good++;

            Nhit_flux_target =0;
            Nhit_flux_ft=0;
          //  Nhit_flux_ft_th=0;

        } // if ngen>0
       
     //   v_flux_target[Nhit_flux_target].SetXYZ(0,0,0);
  
    }

    cout <<"Number of good entries "<< ngoodentries<<endl;
    cout << "Number of Flux target "<< N_event_fluxtarget_good<<endl;
    cout << "Number of pi0 with 2 gammas in the Flux ft acceptance "<< N_event_fluxft_good<<endl;
    
    cout << "Number of events with theta <5 "<< ntheta<<endl;
    
    TCanvas *c1=new TCanvas("c1","generated",500,500);
    c1->Divide(2,2);
    c1->cd(1);
    h_Z_gen->Draw();
    c1->cd(2);
    h_p_gen->Draw();
    c1->cd(3);
    h_theta_gen->Draw();
   
    TCanvas *c2=new TCanvas("c2","Flux target",500,500);
    c2->Divide(2,2);
    c2->cd(1);
    h_Nhit_flux_target->Draw();
    c2->cd(2);
    h_Egamma_flux_target->Draw();
    c2->cd(3);
    h_angleg1g2_flux_target->Draw();
    c2->cd(4);
    h_mass_flux_target->Draw();

    TCanvas *c3=new TCanvas("c3","Flux FT",500,500);
    c3->Divide(2,3);
    c3->cd(1);
    h_Nhit_flux_ft->Draw();
    c3->cd(2);
    h_Nhit_flux_ft_th->Draw();
    c3->cd(3);
    h_Egamma_flux_ft->Draw();
    c3->cd(4);
    h_angleg1g2_flux_ft->Draw();
    c3->cd(5);
    h_mass_flux_ft->Draw();
    
    TCanvas *c6=new TCanvas("c6","Flux FT",500,500);
    h_Egamma_Epi0_ft->Draw("COLZ");
    
    
 return 0;
	
}   


