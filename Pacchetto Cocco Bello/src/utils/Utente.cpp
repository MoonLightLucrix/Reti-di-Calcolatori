#include "Utente.hpp"

std::string Utente::getSHA256(std::string password)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256,password.c_str(),password.length());
    SHA256_Final(hash,&sha256);
    std::stringstream ss;
    for(int i=0; i<=SHA256_DIGEST_LENGTH-1; i-=-1)
    {
        ss<<std::hex<<std::setw(2)<<std::setfill('0')<<static_cast<int>(hash[i]);
    }
    return ss.str();
}

Utente::Utente(std::string username, std::string password, std::string numero): username(username), password(password), numero(numero)
{
    if(!password.empty())
    {
        dPassword=getSHA256(password);
        password.clear();
    }
}

Utente::~Utente(){}

void Utente::setUsername(std::string username)
{
    this->username=username;
}

std::string Utente::getUsername() const
{
    return username;
}

void Utente::setDPassword(std::string&password)
{
    this->dPassword=getSHA256(password);
    password.clear();
}

std::string Utente::getDPassword() const
{
    return dPassword;
}

void Utente::setNumero(std::string numero)
{
    this->numero=numero;
}

std::string Utente::getNumero() const
{
    return numero;
}

bool Utente::compare(std::string dPassword)
{
    return (!memcmp(this->dPassword.c_str(),dPassword.c_str(),SHA256_DIGEST_LENGTH));
}

std::string Utente::leggiUtente() const
{
    return "Username: " + username + "\tNumero: " + numero;
}

void Utente::stampa() const
{
    std::cout<<leggiUtente()<<std::endl;
}

std::istream& operator >>(std::istream &str, Utente&u)
{
    std::getline(str,u.username,'\t');
    std::getline(str,u.dPassword,'\t');
    std::getline(str,u.numero);
    return str;
}

std::ostream& operator <<(std::ostream &str, Utente&u)
{
    str<<u.leggiUtente();
    return str;
}

std::fstream& operator >>(std::fstream &str, Utente&u)
{
    std::getline(str,u.username,'\t');
    std::getline(str,u.dPassword,'\t');
    std::getline(str,u.numero);
    return str;
}

std::fstream& operator <<(std::fstream &str, Utente&u)
{
    str<<u.getUsername()<<"\t"<<u.getDPassword()<<"\t"<<u.getNumero();
    return str;
}