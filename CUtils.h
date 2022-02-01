#pragma once

#include <string>
#include <cstring>

namespace
{
    class CPipeHandle
            {
            public:
                CPipeHandle(FILE *pipe)
                : m_pipe(pipe)
                {
                }

                ~CPipeHandle()
                {
                    if (m_pipe)
                    {
                        pclose(m_pipe);
                    }
                }

                operator FILE*()const
                {
                    return m_pipe;
                }

            private:
                FILE *m_pipe = nullptr;
            };
}

class CUtils
{
public:
    CUtils() = delete;

    static bool RunProcess(std::string const& command);
};

bool CUtils::RunProcess(const std::string &command)
{
    CPipeHandle pipe(popen(command.c_str(), "r"));
    if (!pipe)
    {
        return false;
    }

    std::vector<char> buffer(256);

    while (std::fgets(buffer.data(), int(buffer.size()), pipe))
    {
        std::fputs(buffer.data(), stderr);
    }

    if (std::feof(pipe))
    {
        return true;
    }

    std::fputs(std::strerror(errno), stderr);
    return false;
}
