createTicket(char* typeClass,char* depCity,char* arrCity)
{

char arrayParamName[50];
int price=-1;
int i;
int count_offFly;
	
lr_save_string(typeClass, "typeClass");
lr_save_string(depCity, "depCity");
lr_save_string(arrCity, "arrCity");

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
		
	web_reg_save_param_ex(
    "ParamName=ofFlight", 
    "LB/IC=name=\"outboundFlight\" value=\"",
    "RB/IC=\"",
    "Ordinal=all",
	LAST);
	
	web_reg_save_param_ex(
    "ParamName=priceTicket", 
    "LB/IC=<td align=\"center\">$ ",
    "RB/IC=</TD>",
    "Ordinal=all",
	LAST);
	
	
	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={depCity}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={arrCity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={seat}", ENDITEM, 
		"Name=seatType", "Value={typeClass}", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=62", ENDITEM, 
		"Name=findFlights.y", "Value=7", ENDITEM, 
		LAST);
		
		for (i=1;i<=4;i++) {
		sprintf(arrayParamName, "{priceTicket_%d}", i);
		lr_output_message("Price ticket of %s class - %d -$ %s(%s - %s)",typeClass, i, lr_eval_string(arrayParamName),depCity,arrCity);
		if (atoi(lr_eval_string(arrayParamName)) >=100 && atoi(lr_eval_string(arrayParamName)) <=500 ) {
			price = atoi(lr_eval_string(arrayParamName));
			count_offFly = i;		
		}
		if (i==4 && price == -1) {
			return -1;
		}
	}

	if (count_offFly == 1 ) {
	lr_save_string(lr_eval_string("{ofFlight_1}"),"typeTicket");	
	} else if (count_offFly == 2 ) {
	lr_save_string(lr_eval_string("{ofFlight_2}"),"typeTicket");
	} else if (count_offFly == 3 ) {
	lr_save_string(lr_eval_string("{ofFlight_3}"),"typeTicket");
	} else if (count_offFly == 4 ) {
	lr_save_string(lr_eval_string("{ofFlight_4}"),"typeTicket");
	}

		
	

	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={typeTicket}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={typeClass}", ENDITEM, 
		"Name=seatPref", "Value={seat}", ENDITEM, 
		"Name=reserveFlights.x", "Value=56", ENDITEM, 
		"Name=reserveFlights.y", "Value=7", ENDITEM, 
		LAST);


	web_submit_data("reservations.pl_3", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={name}", ENDITEM, 
		"Name=lastName", "Value={lastname}", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=pass1", "Value={name} {lastname}", ENDITEM, 
		"Name=creditCard", "Value=", ENDITEM, 
		"Name=expDate", "Value=", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value={typeClass}", ENDITEM, 
		"Name=seatPref", "Value={seat}", ENDITEM, 
		"Name=outboundFlight", "Value={typeTicket}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		"Name=buyFlights.x", "Value=32", ENDITEM, 
		"Name=buyFlights.y", "Value=4", ENDITEM, 
		LAST);
		
		lr_output_message("Ticket creation completed!");
		lr_output_message("Price ticket %s, %s class, departed : %s, arrive : %s, Passenger : %s %s.",lr_eval_string(arrayParamName), typeClass, depCity,arrCity,lr_eval_string("{name}"), lr_eval_string("{lastname}"));
				

	return 0;
}