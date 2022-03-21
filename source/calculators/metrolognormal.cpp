//
//  metrolognormal.c
//  Mothur
//
//  Created by Sarah Westcott on 4/25/19.
//  Copyright © 2019 Schloss Lab. All rights reserved.
//

#include "metrolognormal.hpp"

/*constants for calculated compound Poisson lognormal*/

/***********************************************************************/
MetroLogNormal::MetroLogNormal(int fi, double sigx, double sigy, double sigS, int n, string st) : sigmaX(sigx), sigmaY(sigy), sigmaS(sigS), nIters(n), outFileStub(st), fitIters(fi), DiversityCalculator(false) {}
/***********************************************************************/


#ifdef USE_GSL
/***********************************************************************/
double nLogLikelihood1(const gsl_vector * x, void * params)
{
    MothurOut* m = MothurOut::getInstance();
    try {
        double dMDash  = gsl_vector_get(x,0), dV = gsl_vector_get(x,1);
        int    nS = (int) floor(gsl_vector_get(x, 2));
        t_Data *ptData = (t_Data *) params;
        int    i       = 0;
        double dLogL   = 0.0;
        
        DiversityUtils dutils("metroln");
        
        for(i = 0; i < ptData->nNA; i++){
            
            if (m->getControl_pressed()) { break; }
            
            double dLogP = 0.0;
            int    nA    = ptData->aanAbund[i][0];
            
            if(nA < 100){
                dLogP = dutils.logLikelihoodQuad(nA, dMDash, dV);
            }
            else{
                dLogP = dutils.logLikelihoodRampal(nA, dMDash, dV);
            }
            
            dLogL += ((double) ptData->aanAbund[i][1])*dLogP;
            
            dLogL -= gsl_sf_lnfact(ptData->aanAbund[i][1]);
        }
        
        dLogL += (nS - ptData->nL)*dutils.logLikelihoodQuad(0, dMDash, dV);
        
        dLogL -= gsl_sf_lnfact(nS - ptData->nL);
        
        dLogL += gsl_sf_lnfact(nS);
        
        /*return*/
        return -dLogL;
    }catch(exception& e) {
        m->errorOut(e, "MetroLogNormal", "nLogLikelihood1");
        exit(1);
    }
}
/***********************************************************************/
double negLogLikelihood1(double dMDash, double dV, int nS, void * params)
{
    MothurOut* m = MothurOut::getInstance();
    try {
        t_Data *ptData = (t_Data *) params;
        int    i       = 0;
        double dLog0 = 0.0, dLogL   = 0.0;
        
        DiversityUtils dutils("metroln");
        
        for(i = 0; i < ptData->nNA; i++){
            
            if (m->getControl_pressed()) { break; }
            
            double dLogP = 0.0;
            int    nA    = ptData->aanAbund[i][0];
            
            if(nA < 100){
                dLogP = dutils.logLikelihoodQuad(nA, dMDash, dV);
            }
            else{
                dLogP = dutils.logLikelihoodRampal(nA, dMDash, dV);
            }
            
            dLogL += ((double) ptData->aanAbund[i][1])*dLogP;
            
            dLogL -= gsl_sf_lnfact(ptData->aanAbund[i][1]);
        }
        
        dLog0     = dutils.logLikelihoodQuad(0, dMDash, dV);
        
        if(nS > ptData->nL){
            dLogL += (nS - ptData->nL)*dLog0;
        }
        
        dLogL -= gsl_sf_lnfact(nS - ptData->nL);
        
        dLogL += gsl_sf_lnfact(nS);
    
        return -dLogL;
        
    }catch(exception& e) {
        m->errorOut(e, "MetroLogNormal", "negLogLikelihood1");
        exit(1);
    }
}
/***********************************************************************/
void* metropolis1 (void * pvInitMetro) {
    MothurOut* m = MothurOut::getInstance();
    try {
        t_MetroInit *ptMetroInit  = (t_MetroInit *) pvInitMetro;
        gsl_vector  *ptX          = ptMetroInit->ptX;
        t_Data      *ptData       = ptMetroInit->ptData;
        t_Params    *ptParams     = ptMetroInit->ptParams;
        gsl_vector  *ptXDash      = gsl_vector_alloc(3); /*proposal*/
        
        const gsl_rng_type *T;
        gsl_rng            *ptGSLRNG;
        
        int nS = 0, nSDash = 0,nIter = 0;
        double dRand = 0.0, dNLL = 0.0;
        void   *pvRet = nullptr;
        double dM = 0.0, dV = 0.0;
        double dMDash = 0.0, dVDash = 0.0;
        double dXDash = 0.0, dX = 0.0;
        
        /*set up random number generator*/
        T        = gsl_rng_default;
        ptGSLRNG = gsl_rng_alloc (T);
        
        nS = (int) floor(gsl_vector_get(ptX,2));
        
        dNLL = negLogLikelihood1(gsl_vector_get(ptX,0), gsl_vector_get(ptX,1), nS,(void*) ptData);
        
        dM = gsl_vector_get(ptX,0); dV = gsl_vector_get(ptX,1);
        gsl_vector_set(ptX,0,dM + 0.5*dV);
        
        string filename = ptParams->szOutFileStub + "_" + toString(ptMetroInit->nThread) + ".sample";
        
        ofstream out; Utils util; util.openOutputFile(filename, out);
        out.setf(ios::fixed, ios::floatfield); out.setf(ios::showpoint);
        
        /*seed random number generator*/
        gsl_rng_set(ptGSLRNG, ptMetroInit->lSeed);
        
        DiversityUtils dutils("metroln");
        
        /*now perform simple Metropolis algorithm*/
        while(nIter < ptParams->nIter){
            double dA = 0.0, dNLLDash = 0.0;
            
            if (m->getControl_pressed()) { break; }
            
            dutils.getProposal(ptGSLRNG, ptXDash, ptX, &nSDash, nS,ptParams);
            
            dXDash =  gsl_vector_get(ptXDash,0); dVDash = gsl_vector_get(ptXDash,1);
            dMDash =  dXDash - 0.5*dVDash;
            dNLLDash = negLogLikelihood1(dMDash, dVDash, nSDash, (void*) ptData);
            
            dA = exp(dNLL - dNLLDash);
            if(dA > 1.0){
                dA = 1.0;
            }
            
            dRand = gsl_rng_uniform(ptGSLRNG);
            
            if(dRand < dA){
                ptMetroInit->nAccepted++;
                gsl_vector_memcpy(ptX, ptXDash);
                nS = nSDash;
                dNLL = dNLLDash;
            }
            
            if(nIter % 10 == 0){
                dX =  gsl_vector_get(ptX,0); dV = gsl_vector_get(ptX,1);
                dM =  dX - 0.5*dV;
                
                out << nIter << "," << dM << "," << dV << "," << nS << "," << dNLL << endl;
                
            }
            
            nIter++;
        }
        out.close();
        
        /*free up allocated memory*/
        gsl_vector_free(ptXDash);
        gsl_rng_free(ptGSLRNG);
        
        return pvRet;

    }catch(exception& e) {
        m->errorOut(e, "MetroLogNormal", "metropolis1");
        exit(1);
    }
}
#endif
/***********************************************************************/
vector<string> MetroLogNormal::getValues(SAbundVector* rank){
    try {
        
        t_Params tParams; tParams.nIter = nIters; tParams.dSigmaX = sigmaX; tParams.dSigmaY = sigmaY; tParams.dSigmaS = sigmaS; tParams.szOutFileStub = outFileStub; tParams.lSeed = m->getRandomSeed();
        t_Data   tData;
        
        int bestSample = 0;
        
#ifdef USE_GSL
        
        DiversityUtils dutils("metroln");
        
        dutils.loadAbundance(&tData, rank);

        gsl_vector* ptX = gsl_vector_alloc(3);
        
        gsl_rng_env_setup();

        gsl_set_error_handler_off();

        dutils.loadAbundance(&tData, rank);
        
        int sampled = rank->getNumSeqs(); //nj
        int numOTUs = rank->getNumBins(); //nl

        gsl_vector_set(ptX, 0, 1.0); //INIT_M_DASH
        gsl_vector_set(ptX, 1, 1.0); //INIT_V
        gsl_vector_set(ptX, 2, numOTUs*2);

        double chaoResult = dutils.chao(&tData);
        m->mothurOut("\nMetroLogNormal - D = " + toString(numOTUs) + " L = " + toString(sampled) +  " Chao = " + toString(chaoResult) +  "\n");

        dutils.minimiseSimplex(ptX, 3, (void*) &tData, &nLogLikelihood1, 1.0, 1.0e-2, 100000);

        vector<double> parameterResults = dutils.outputResults(ptX, &tData, &nLogLikelihood1);
        
        if(tParams.nIter > 0){
            
            vector<double> acceptanceRates = dutils.mcmc(&tParams, &tData, ptX, &metropolis1); //sigmaX 0.1
            
            if (fitIters != 0) { bestSample = dutils.fitSigma(acceptanceRates, parameterResults, fitIters, &tParams, &tData, ptX, &metropolis1); }
            
        }
        
        
        /*free up allocated memory*/
        gsl_vector_free(ptX);
        
        dutils.freeAbundance(&tData);
        
#endif
        
        outputs.push_back(outFileStub + "_" + toString(bestSample) + ".sample");
        if (bestSample == 0) {  outputs.push_back(outFileStub + "_1.sample"); outputs.push_back(outFileStub + "_2.sample");  }
        else if (bestSample == 1) {  outputs.push_back(outFileStub + "_0.sample"); outputs.push_back(outFileStub + "_2.sample");  }
        else if (bestSample == 2) {  outputs.push_back(outFileStub + "_0.sample"); outputs.push_back(outFileStub + "_1.sample");  }
        
        return outputs;
    }
    catch(exception& e) {
        m->errorOut(e, "MetroLogNormal", "getValues");
        exit(1);
    }
}
/***********************************************************************/


