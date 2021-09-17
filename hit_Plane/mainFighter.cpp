# include "fighter.h"
# include <iostream>	

  int main(void)
{
	init();            
	while (1)
	{
		drawPicture();     
		pcOperate();    
		operateFighger();  
	}

	return 0;
}

