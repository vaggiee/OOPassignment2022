void chooseattack ()
 if (strengthlevelc1 < strengthlevelc2)
    {      
         //c2 attacks , c1 tries to move
        healthlevelc1 = strengthlevelc2 - defencec1;
     } 
     else {
         //c1 attacks , c2 tries to move
         healthlevelc2 = strengthlevelc1 - defencec2;
    }
  }