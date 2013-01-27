#pragma once


class TextReader
{
    char *m_data;
    unsigned int m_size;
    unsigned int m_pos;
    std::vector<char> m_buffer;

public:
    TextReader(char* data, unsigned int size)
    : m_data(data), m_size(size), m_pos(0)
    {
    }

    Line &gets(Line &line)
    {
        m_buffer.clear();
        for(; m_pos<m_size; ++m_pos){
            char c=m_data[m_pos];
            if(c=='\n'){
                ++m_pos;
                break;
            }
            m_buffer.push_back(c);
        }
        if(m_buffer.empty()){
            line.assign(0, 0);
        }
        else{
            line.assign(&m_buffer[0], &m_buffer[0]+m_buffer.size());
        }
        return line;
    }

    bool eof()const
    {
        return m_pos>=m_size;
    }
};

