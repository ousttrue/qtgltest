#pragma once


class Line
{
    FixedString  m_line;
    unsigned int m_pos;
    std::vector<char> m_buffer;

public:
    Line(const char* begin, const char* end)
    : m_line(begin, end), m_pos(0)
    {
    }

    void assign(const char* begin, const char* end)
    {
        m_line=FixedString(begin, end);
        m_pos=0;
    }

    bool operator==(const char *rhs)const
    {
        for(auto it=m_line.begin(); it!=m_line.end(); ++it, ++rhs){
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

    FixedString get()
    {
        m_buffer.clear();
        for(; m_pos<m_line.size(); ++m_pos){
            char c=m_line[m_pos];
            if(c==' '){
                ++m_pos;
                break;
            }
            m_buffer.push_back(c);
        }
        if(m_buffer.empty()){
            return FixedString(0, 0);
        }
        return FixedString(&m_buffer[0], &m_buffer[0]+m_buffer.size());
    }
};


