# boitapotard_HID

microcontroller potentiometer value to html through USB HID  
transfert des valeurs d'un potentiomètre connecté en A1 via USB-HID (message clavier)

Permet de connecter un µc à une tablette et smartphone et de transférer la valeur du potard à la page web.

Le µc ne renvoie la valeur que si elle est différente des 2 dernières (évite le flicking entre 2 valeurs)  
le µc envoie la valeur du potard (_int_ entre 0-127)  

exemple :  
valeur du potard = 127  
message reçu = "Digit1" + "Digit2" + "Digit7" + "Enter"  


La page HTML  :  
- gère les erreurs : chiffre > à 127 (manque un 'Enter' entre 2 envois)
- envoie les 'chiffres' dans un array
- fabrique une chaine avec le contenu de l'array et la transtype en nombre (reconstitue le nombre envoyé) quand reçoit 'Enter', 

Testé sur :  
iPadOs (16.2) : Firefox, Chrome, Safari Mobile  
Android (9) : Firefox, Chrome
