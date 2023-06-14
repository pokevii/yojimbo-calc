#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

  class Yojimbo{

    private:
      float motivation;
      int bm;         //base motivation
      int cp;         //compatibility points 
      float zr;       //zanmato resistance
      int zl;         //zanmato level of the enemy
      int cf;         //choice made
      bool overdrive; //overdrive factor
      int gil;        //gil paid
      int totalGil;   //total gil. only matters if choice 1 was made.
      int version;    //version of FFX
      
      int calculateBM(int payment){ //base motivation is calculated based on how much yojimbo was paid.
        int baseMotivation = 0;
        int lowRange;
        int hiRange;
        int loopAmount = 30;

        if(payment == 0){
          cp -= 20;   //paying yojimbo 0 gil will result in losing 20 compatibility.
          return 0;   //yojimbo immediately dismisses himself.
        }

        for(int i=1; i<loopAmount; i++){
          i == 1 ? lowRange = 1 : lowRange = pow(2, i);
         
          if(version == 2 && i >= 15){   //in the original NTSC/JP version, yojimbo's motivation caps out at 56 (65535 gil)
            hiRange = gilCap;
          } else {
            hiRange = (pow(2, i+1)-1);
          }
          
          if(payment >= lowRange && payment <= hiRange){
            baseMotivation = 4 * (i-1);
            return baseMotivation;
          }
        }
        return -1;
      }

      //https://www.neoseeker.com/final-fantasy-x/faqs/65600-yojimbo-a.html
      //https://finalfantasy.fandom.com/wiki/Yojimbo_(summon)#Abilities
      float motivationCalculator()
      {
        srand(time(NULL));

        float zchance;
        int motivation1 = bm;
        std::cout << motivation1 << std::endl;
        int motivation2 = motivation1 + floor(cp / 4);
        int motivation3 = motivation2;
        if(cf == 1){
          motivation3 = floor(motivation2 * (0.75 + (gil * 0.5 / totalGil)));
        }

        if(cf == 1 || cf == 2){
          switch(zl){
            case 1:
            default:  zr = 1; break;
            case 2: zr = 0.5; break;
            case 3: zr = 0.33; break;
            case 4: zr = 0.25; break;
            case 5: zr = 0.20; break;
            case 6: zr = 0.16; break;
          }
        }
        else if(cf == 3)
        {
          if(zl >= 1 && zl <= 3) zr = 0.8;
          else zr = 0.4;
        }

        int motivation4 = floor(motivation3 * zr);
        std::cout << "motivation4 = " << motivation4 << std::endl;
        int motivation5 = motivation4 + (overdrive ? version == 1 ? 20 : 2 : 0);

        //Calculate odds of Zanmato
        zchance = (float(motivation5) - 16.0)/64.0;
        if(zchance < 0) zchance = 0;
        printf("Chance for zanmato: %f%\n", zchance);

        std::cout << "motivation5 = " << motivation5 << std::endl;
        int motivation6 = motivation5 + rand()%64;
        std::cout << "motivation6 = " << motivation6 << std::endl;

        //The game recalculates here if motivation6 < 80. The enemy's zanmato level is set to 1 during recalculation.
        //First 3 steps are the same as before so I will just reuse the motivation3 variable here.
        if(motivation6 < 80){
          if(cf == 1 || cf == 2){
            zr = 1;
          } else zr = 0.8;

          int motivation4b = floor(motivation3 * zr);
          int motivation5b = motivation4b + (overdrive ? version == 1 ? 20 : 2 : 0);

          //Calculate odds of Zanmato
          zchance = (float(motivation5b) - 16.0)/64.0;
          if(zchance < 0) zchance = 0;
          printf("Chance for zanmato: %f%\n", zchance);

          int motivation6b = motivation5b + rand()%64;
          return motivation6b;
        } else {
          return motivation6;
        }
      }

    public:
      const static int gilCap = 999999999;

      Yojimbo(){
        setBM(56);
        setCP(50);
        setZR(1);
        setCF(2);
        setOverdrive(false);
        setVer(1);
      }

      Yojimbo(int version, int payment){
        setGil(payment);
        setVer(version);
        bm = calculateBM(payment);
        setCP(50);
        setZR(1);
        setZL(4);
        setCF(2);
        setOverdrive(false);
      }

      void displayStats(){
        printf("///- YOJIMBO'S STATS -///\n");
        printf("Motivation: %.2f\n", motivation);
        printf("Base Motivation: %i\n", bm);
        printf(" └ Paid %i gil\n", gil);
        printf("Compatibility: %i\n", cp);
        printf("Overdrive: %s\n\n", overdrive ? "true" : "false");
        printf("///- OTHER     STATS -///\n");
        printf("Enemy Zanmato Resistance: %.1f\n", zr);
        printf("Cave Choice: %i\n", cf);
        printf("Version of FFX: %s\n", version == 1 ? "HD Remaster / PAL / International" : "Original JP / Original NTSC");
      }
      
      float getMotivation()   {return motivation;};
      int getBM()             {return bm;};
      int getCP()             {return cp;};   
      float getZR()           {return zr;};  
      int getZL()             {return zl;}; 
      int getCF()             {return cf;};  
      int getGil()            {return gil;};  
      int getTotalGil()       {return totalGil;};
      int getVer()            {return version;};
      bool getOverdrive()     {return overdrive;};   

      void setMotivation(float f) {motivation = f;};
      void setBM(int i)           {bm = i;};
      void setZR(float f)         {zr = f;};
      void setZL(int i)           {zl = i;};
      void setCF(int i)           {cf = i;};
      void setGil(int i)          {gil = i;};
      void setTotalGil(int i)     {totalGil = i;};
      void setVer(int i)          {version = i;};
      void setOverdrive(bool b)   {overdrive = b;};

      void setCP(int i){    //cp is a value from 0-255
        if(i >= 0 && i <= 255) { cp = i; } 
        else{
          std::cout << "compatibility invalid, defaulting to 128";
          cp = 128;
        }
      }


      void attack(){
        setMotivation(motivationCalculator());
        if(motivation >= 0 && motivation <= 30){
          std::cout << "Yojimbo uses Daigoro! He shakes his head in disapproval...\n";
          setCP(cp - 1);
        }
        else if(motivation >= 31 && motivation <= 47){
          std::cout << "Yojimbo throws several Kozuka at a single foe!\n";
        }
        else if(motivation >= 48 && motivation <= 63){
          std::cout << "Yojimbo draws his powerful Wakizashi and uses it against one target!\n";
          setCP(cp + 1);
        }
        else if(motivation >= 64 && motivation < 80){
          std::cout << "Yojimbo draws his powerful Wakizashi and attacks several enemies with it!\n";
          setCP(cp + 3);
        }
        else if(motivation >= 80){
          std::cout << "Yojimbo uses Zanmato, instantly killing a zanmato level " << zl << " enemy!\n";
          setCP(cp + 4);
        }
      }
  };