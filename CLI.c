CLI()
{
	int i,j;
	int isCompleted = -1;
	char typeClassArray[3][10] = {"First", "Business", "Coach"};
	char departCity[3][15]={"Denver","London","Paris"};
	char arriveCity[3][15]={"Sydney", "Portland", "Seattle"};
	
	for (j=0;j<=2;j++){
	for (i=0; i<=2; i++) {
			isCompleted = createTicket(typeClassArray[i],departCity[j],arriveCity[j]);
		if (isCompleted == 0) {
			return 0;
		}
	}
	}
	return 0;
}
