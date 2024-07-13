#include<iostream>
#include<string>




std::string OperatieXOR(std::string sir1, std::string sir2)
{
	std::string rezultat = "";
	

	for (int index = 0; index < sir1.length(); index++) {

		if (sir1[index] == sir2[index])
			rezultat += "0";
		else
			rezultat += "1";
	}

	return rezultat; 

}


void FunctieCodRedundantaCiclica(std::string mesaj, std::string polinomGenerator) {

	for (char caracter : mesaj) {

		if (caracter != '0' && caracter != '1') {
			std::cout << "Mesajul nu este in format binar. Va rugam introduceti doar caractere de 0 si 1" << "\n";
			return;
		}

	}


	for (char caracter : polinomGenerator) {

		if (caracter != '0' && caracter != '1') {
			std::cout << "Polinomul generator nu este in format binar. Va rugam introduceti doar caractere de 0 si 1" << "\n";
			return;
		}

	}

	if (mesaj.length() <= polinomGenerator.length()) {

		std::cout << "Lungimea mesajului trebuie sa fie mai mare decât lungimea sirului format din coeficientii polinomului!" << "\n";
		return;

	}

	std::cout << "Polinomul generator are gradul " << polinomGenerator.length() - 1 << " si deci numarul de zerouri de adaugat la mesajul extins este " << polinomGenerator.length() - 1<<  "\n" << "\n";

	std::string mesajExtins = mesaj + std::string(polinomGenerator.length() - 1, '0');

	std::cout << "Mesajul initial extins este: " << mesaj << " + " << std::string(polinomGenerator.length() - 1, '0') << " = " << mesajExtins << 
		" (acesta este format prin concatenarea mesajului inital si al numarului de zerouri mentionat la linia anterioara) " << "\n" << "\n";

	std::cout << "-------------------------------------------------------------------------------------------------------------------" << "\n" << "\n";

	while (mesajExtins.length() >= polinomGenerator.length()) {

		std::string rezultatXOR = OperatieXOR(mesajExtins.substr(0, polinomGenerator.length()), polinomGenerator);


		std::string rezultatXORPolinomRest = rezultatXOR + mesajExtins.substr(polinomGenerator.length());

		std::cout << "Opearatia XOR este formata din adunarea dintre: " << mesajExtins << " + " << polinomGenerator << " = " << rezultatXORPolinomRest << "\n";

		size_t pozitie = rezultatXORPolinomRest.find_first_not_of('0');

		if (pozitie != std::string::npos)
			rezultatXORPolinomRest = rezultatXORPolinomRest.substr(pozitie);
		else
			rezultatXORPolinomRest = "0"; 

		
		mesajExtins = rezultatXORPolinomRest; 

		
		std::cout << "Mesajul extins este: " << mesajExtins << "\n" << "\n";

	}

	std::string sirZerouri = std::string(polinomGenerator.length() - 1, '0');

	std::cout << "Sirul format din zerourile adaugate initial pe baza gradului polinomului este: " << sirZerouri << "\n";

	std::string rezultatFinal = OperatieXOR(sirZerouri, mesajExtins);


	std::cout << "Rezultatul final este: " << rezultatFinal << "\n";

	std::string mesajTransmis = mesaj + rezultatFinal;

	std::cout << "Mesajul transmis catre destinatar este: " << mesajTransmis << "\n";
    

}

int main() {

	std::string mesaj, polinomGenerator;

	std::cout << "DATE INITIALE" << "\n";
	std::cout << "-------------------------------------------------------------------------------------------------------------------" << "\n" << "\n";


	std::cout << "Introduceti mesajul in format binar (caractere de 0 si 1):  ";
	std::cin >> mesaj;
	std::cout << "\n";

	std::cout << "Introduceti polinomul generator in format binar (caractere de 0 si 1):  ";
	std::cin >> polinomGenerator;
	std::cout << "\n";

	
	std::cout << "APLICARE SI EXPLICARE A CODULUI DE REDUNDANTA CICLICA" << "\n";
	std::cout << "-------------------------------------------------------------------------------------------------------------------" << "\n" << "\n";


	FunctieCodRedundantaCiclica(mesaj, polinomGenerator); 

	return 0; 

}
