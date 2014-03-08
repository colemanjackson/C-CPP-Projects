
# $Id: rule30.el 1970 2013-10-30 01:23:48Z asminer $

Elementary = {
  Name = "Rule 30";

  Rule = 30;

  Terrain = {
    Xrange = -30..30;
    Yrange = -30..0;
  };

  Chars = {
    Zero = 46;
    One  = 35;
  };

  Colors = {
    Zero = (255, 255, 255);
    One  = (64, 64, 64);
  };

  Initial = {
    One  = (0, 0);
  };
};
