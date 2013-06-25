#pragma once


class BinaryReader
{
    const char* m_data;
    unsigned int m_size;
    unsigned int m_pos;

public:
    BinaryReader(const char* data, unsigned int size)
        : m_data(data), m_size(size), m_pos(0)
    {
    }

    const char* current()const
    {
        return &m_data[m_pos];
    }

    std::string getString(unsigned int size)
    {
        const char* end=current();
        for(unsigned int i=0; i<size; ++i, ++end){
            if(*end=='\0'){
                break;
            }
        }
        std::string s(current(), end);
        m_pos+=size;
        return s;
    }

    template<typename T>
        T &get(T &t)
        {
            t= *((T*)current());
            m_pos+=sizeof(T);
            return t;
        }
};

