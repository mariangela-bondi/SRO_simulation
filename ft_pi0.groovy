
import org.jlab.io.hipo.*;
import org.jlab.io.hipo.HipoDataSource;
import org.jlab.io.base.DataBank;
import org.jlab.io.base.DataEvent;
import org.jlab.clas.physics.Particle;
import org.jlab.groot.data.H1F;
import org.jlab.groot.data.H2F;
import org.jlab.groot.math.F1D;
import org.jlab.groot.ui.TCanvas;
import org.jlab.groot.fitter.DataFitter;



H1F hpi0 = new H1F("hpi0", 100, 50.0, 250.0);
hpi0.setTitleX("M (MeV)");
hpi0.setTitleY("Counts");
hpi0.setTitle("2#gamma invariant mass");
hpi0.setFillColor(3);

//F1D fpi0 = new F1D("fpi0", "[amp]*gaus(x,[mean],[sigma])+[p0]+[p1]*x", 115.0, 160.0);
F1D fpi0 = new F1D("fpi0", "[amp]*gaus(x,[mean],[sigma])", 115.0, 160.0);
fpi0.setParameter(0, 0.0);
fpi0.setParameter(1, 140.0);
fpi0.setParameter(2, 4.0);
//fpi0.setParameter(3, 0.0);
//fpi0.setParameter(4, 0.0);
fpi0.setLineWidth(2);
fpi0.setOptStat("1111111");

H2F hmassangle = new H2F("hmassangle", 100, 0.0, 300.0, 100, 0.0, 6.0);
hmassangle.setTitleX("M (MeV)");
hmassangle.setTitleY("Angle (deg)");
hmassangle.setTitle("Angle vs. Mass");

H2F hxy_cluster = new H2F("hxy_cluster", 200,-20,20,200,-20,20);
hxy_cluster.setTitleX("X");
hxy_cluster.setTitleY("Y");
hxy_cluster.setTitle("X vs. Y");



H2F hEclusterpimass = new H2F("hEclusterpimass", 100, 0.0, 300.0, 100, 100.0, 8500.0)
hEclusterpimass.setTitleX("M (MeV)");
hEclusterpimass.setTitleY("E (MeV)");
hEclusterpimass.setTitle("M vs. E");


int nevent = -1;
int npi0=0;

HipoDataSource reader = new HipoDataSource();
reader.open(args[0]);

while(reader.hasEvent()) {
      nevent++;
      if(nevent%10000 == 0) System.out.println("Analyzed " + nevent + " events");

      DataEvent event = reader.getNextEvent();
      if(event.hasBank("RUN::config") && event.hasBank("REC::Particle") && event.hasBank("REC::ForwardTagger")) {
      
         ArrayList<Particle> gammas = new ArrayList();

         int ind_test=0;
         DataBank runConf = event.getBank("RUN::config");
         DataBank recBank = event.getBank("REC::Particle");
         DataBank recFT   = event.getBank("REC::ForwardTagger");
//System.out.println("mmmmm "+ recBank.rows());
         float[] xcl = new float[recBank.rows()];
         float[] ycl = new float[recBank.rows()];
         for(int loop = 0; loop < recBank.rows(); loop++)
         {
	     int pid    = recBank.getInt("pid", loop);
	     int status = recBank.getShort("status", loop);
	     int detect = (int) (status/1000);
	     if(detect==1 && pid==22) {
	        Particle recParticle = new Particle(pid,
                            recBank.getFloat("px",loop),
						    recBank.getFloat("py",loop),
						    recBank.getFloat("pz",loop),
						    0,0,0);
	        double energy = recParticle.e();
		double theta  = Math.toDegrees(recParticle.theta());
		int    size   = 0;
        float x_cl=0;
        float y_cl=0;
		for(int k=0; k<recFT.rows(); k++) {
            if(recFT.getShort("pindex",k)==loop) {
               size=recFT.getShort("size",k);
               x_cl = recFT.getFloat("x",k);
               y_cl = recFT.getFloat("y",k);
                                                 }
}
              
                  if(energy>0.3 && size > 1 && theta>2.5 && theta<4.5) {
                   gammas.add(recParticle);
                   xcl[ind_test] = x_cl;
                   ycl[ind_test] = y_cl;
       //   System.out.println(""+xcl[ind_test]+" "+ind_test);
                   ind_test = ind_test+1;
		} // end if energy e theta
             }// end if detec and pid==22
	 } //end for loop
     
         if(gammas.size()>=2) {
            for(int i1 = 0; i1 < gammas.size(); i1++) {
                for(int i2 = i1 + 1; i2 < gammas.size(); i2++) {
                  //  System.out.println(xcl[i1]);
                    Particle partGamma1 = gammas.get(i1);
                    Particle partGamma2 = gammas.get(i2);
                    Particle partPi0 = new Particle();
                    partPi0.copy(partGamma1);
                    partPi0.combine(partGamma2, +1);
                    double invmass = Math.sqrt(partPi0.mass2());
                    double angle = Math.toDegrees(Math.acos(partGamma1.cosTheta(partGamma2)));
                    if(angle>0) hpi0.fill(invmass*1000);
                    hmassangle.fill(invmass*1000, angle);
                    hEclusterpimass.fill(invmass*1000,partGamma1.e()*1000);
                    hEclusterpimass.fill(invmass*1000,partGamma2.e()*1000);
                    if(invmass*1000 <150 && invmass*1000>125) {
                    hxy_cluster.fill(xcl[i1], ycl[i1]);
                    hxy_cluster.fill(xcl[i2], ycl[i2]);
                    System.out.println(xcl[i1]);
                    System.out.println(xcl[i2]);
                    npi0 = npi0 +1;
                    System.out.println("find " + npi0 + " pi0");
                    
} // if  mass
                } // end for i2
            } // end for i1
	 }    //end if gammas.size
      }   
}   
reader.close();
System.out.println("Analyzed " + nevent + " events");

TCanvas pi0 = new TCanvas("pi0", 800, 1200);
pi0.divide(1,2);
pi0.getCanvas().setGridX(false); pi0.getCanvas().setGridY(false);
pi0.getCanvas().setAxisFontSize(18);
pi0.getCanvas().setAxisTitleSize(24);
pi0.cd(0);
double hAmp  = hpi0.getBinContent(hpi0.getMaximumBin());
double hMean = hpi0.getAxis().getBinCenter(hpi0.getMaximumBin());
double hRMS  = 10; 
 fpi0.setParameter(0, hAmp);
 fpi0.setParLimits(0, hAmp*0.8, hAmp*1.2);
 fpi0.setParameter(1, hMean);
 fpi0.setParLimits(1, hMean-hRMS, hMean+hRMS);
 DataFitter.fit(fpi0,hpi0,"LQ");
pi0.draw(hpi0);
pi0.cd(1);
pi0.draw(hmassangle);


TCanvas pi02 = new TCanvas("pi02", 800, 1200);
pi02.divide(1,2);
pi02.getCanvas().setGridX(false); pi0.getCanvas().setGridY(false);
pi02.getCanvas().setAxisFontSize(18);
pi02.getCanvas().setAxisTitleSize(24);
pi02.cd(0);
pi02.draw(hEclusterpimass);
pi02.cd(1);
pi02.draw(hxy_cluster);


