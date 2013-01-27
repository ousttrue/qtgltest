#pragma once


class FixedString
{
    const char *m_begin;
    const char *m_end;
public:
    FixedString(const char *begin, const char *end)
    : m_begin(begin), m_end(end)
    {
    }

    const char* begin()const{ return m_begin; }
    const char* end()const{ return m_end; }
    size_t size()const{ return m_end-m_begin; }
    char operator[](size_t index)const{ return m_begin[index]; }

    bool operator==(const char *rhs)const
    {
        for(auto it=m_begin; it!=m_end; ++it, ++rhs){
            if(*rhs=='\0'){
                return false;
            }
            if(*it!=*rhs){
                return false;
            }
        }
        return *rhs=='\0';
    }

    bool operator!=(const char *rhs)const
    {
        return !((*this)==rhs);
    }

    int toInt()
    {
        return atoi(std::string(m_begin, m_end).c_str());
		/*
        int num=0;
        for(auto it=m_begin; it!=m_end; ++it){
            num=num*10+((*it)-'0');
        }
        return num;
		*/
    }

    float toFloat()
    {
        return static_cast<float>(atof(std::string(m_begin, m_end).c_str()));
    }
};

