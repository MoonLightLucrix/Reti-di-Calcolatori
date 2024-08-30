#include "DatabaseManager.hpp"

DatabaseManager::DatabaseManager(std::string filename, std::string semName): filename(filename), semName(semName), mutex(nullptr)
{
    if(!this->semName.empty())
    {
        if(!openSemaphore(semName))
        {
            exit(EXIT_FAILURE);
        }
    }
    if(!this->filename.empty())
    {
        if(!openFile(filename))
        {
            exit(EXIT_FAILURE);
        }
    }
}

DatabaseManager::~DatabaseManager()
{
    if(mutex)
    {
        sem_close(mutex);
    }
    if(database.is_open())
    {
        database.close();
    }
}

bool DatabaseManager::openFile(std::string filename)
{
    if(this->filename.empty())
    {
        this->filename=filename;
    }
    if(!database.is_open())
    {
        char pathName[filename.length()+1];
        strcpy(pathName,filename.c_str());
        this->path.assign(dirname(pathName));
        database.open(filename,std::ios::in | std::ios::out);
        if(!database.is_open())
        {
            std::cerr<<"open: "<<strerror(errno)<<std::endl;
            return false;
        }
    }
    else
    {
        std::cout<<"open: Can't open another file"<<std::endl;
    }
    return true;
}

bool DatabaseManager::openSemaphore(std::string semName)
{
    if(this->semName.empty())
    {
        this->semName=semName;
    }
    if(mutex)
    {
        std::cout<<"sem_open: Can't open another semaphore"<<std::endl;
    }
    else
    {
        if((mutex=sem_open(semName.c_str(),O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,1))==SEM_FAILED)
        {
            std::cerr<<"sem_open: "<<strerror(errno)<<std::endl;
            return false;
        }
    }
    return true;
}

void DatabaseManager::insert(const std::string line)
{
    sem_wait(mutex);
    database.clear();
    database.seekg(0,std::ios::end);
    database<<line<<std::endl;
    sem_post(mutex);
}

void DatabaseManager::insert(std::stringstream&row)
{
    sem_wait(mutex);
    database.clear();
    database.seekg(0,std::ios::end);
    database<<row.str()<<std::endl;
    sem_post(mutex);
}

std::string DatabaseManager::find(__uint32_t id)
{
    sem_wait(mutex);
    database.clear();
    database.seekg(0);
    std::stringstream ss;
    std::string line;
    __uint32_t aid;
    while(std::getline(database,line))
    {
        ss.str(line);
        ss>>aid;
        if(id==aid)
        {
            sem_post(mutex);
            return line;
        }
        ss.clear();
    }
    sem_post(mutex);
    return "";
}

std::string DatabaseManager::find(std::string id)
{
    sem_wait(mutex);
    database.clear();
    database.seekg(0);
    std::stringstream ss;
    std::string line, aid;
    while(std::getline(database,line))
    {
        ss.str(line);
        std::getline(ss,aid,'\t');
        if(id==aid)
        {
            sem_post(mutex);
            return line;
        }
        ss.clear();
    }
    sem_post(mutex);
    return "";
}

std::string DatabaseManager::nextLine()
{
    static bool isFirstTime=true;
    std::string line;
    if(isFirstTime)
    {
        sem_wait(mutex);
        database.clear();
        database.seekg(0);
        isFirstTime=false;
    }
    if(std::getline(database,line))
    {
        return line;
    }
    else
    {
        isFirstTime=true;
        sem_post(mutex);
    }
    return "";
}

bool DatabaseManager::deleteOrEditLine(__uint32_t id, std::string newLine)
{
    sem_wait(mutex);
    database.seekg(0);
    std::string tmpFilePath=path + "/tmpFile";
    std::fstream tmpOut(tmpFilePath,std::ios::out);
    if(!tmpOut.is_open())
    {
        sem_post(mutex);
        return false;
    }
    std::stringstream ss;
    std::string aLine;
    __uint32_t aid;
    while(std::getline(database,aLine))
    {
        ss.str(aLine);
        ss>>aid;
        if(id!=aid)
        {
            tmpOut<<aLine<<std::endl;
            tmpOut.flush();
        }
        else
        {
            if(!newLine.empty())
            {
                tmpOut<<newLine<<std::endl;
                tmpOut.flush();
            }
        }
        ss.clear();
    }
    database.close();
    database.open(filename,std::ios::in | std::ios::out | std::ios::trunc);
    if(!database.is_open())
    {
        std::cerr<<"open: "<<strerror(errno)<<std::endl;
        sem_post(mutex);
        return false;
    }
    tmpOut.seekg(0);
    database<<tmpOut.rdbuf();
    database.flush();
    tmpOut.close();
    unlink("tmpFile");
    sem_post(mutex);
    return true;
}

bool DatabaseManager::deleteOrEditLine(std::string line, std::string newLine)
{
    sem_wait(mutex);
    database.seekg(0);
    std::fstream tmpOut("tmpFile",std::ios::in | std::ios::out | std::ios::app);
    if(!tmpOut.is_open())
    {
        std::cerr<<"open: "<<strerror(errno)<<std::endl;
        sem_post(mutex);
        return false;
    }
    std::string aLine;
    while(std::getline(database,aLine))
    {
        if(line!=aLine)
        {
            tmpOut<<aLine<<std::endl;
            tmpOut.flush();
        }
        else
        {
            if(!newLine.empty())
            {
                tmpOut<<newLine<<std::endl;
                tmpOut.flush();
            }
        }
    }
    database.close();
    database.open(filename,std::ios::in | std::ios::out | std::ios::trunc);
    if(!database.is_open())
    {
        std::cerr<<"open: "<<strerror(errno)<<std::endl;
        sem_post(mutex);
        return false;
    }
    tmpOut.seekg(0);
    database<<tmpOut.rdbuf();
    database.flush();
    tmpOut.close();
    unlink("tmpFile");
    sem_post(mutex);
    return true;
}