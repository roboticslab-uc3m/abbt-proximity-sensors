void coor() {

  Avect = IR[0][0];
  Bvect = IR[0][1];
  Cvect = IR[0][2];

  x = Avect -  (.5 * Bvect ) - ( .5 * Cvect); // integer math
  y = (.866 * Bvect) - (.866 * Cvect);

  angle = atan2((float)y, (float)x) * 57.296 + 180 ; // convert to degrees and lose the neg values
  Tvect = (long)sqrt( x * x + y * y);


  Serial.print(x);
  Serial.print("/");
  Serial.print(y);
  Serial.print("/");
  Serial.print("\n");
}

