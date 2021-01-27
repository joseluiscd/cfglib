#include "toml.hpp"
#include <fstream>

namespace cfg {

class Cfg {
public:
    class Section {
        friend class Cfg;

    public:
        template <typename T>
        Section& add_value(const std::string& name, T& value)
        {
            if (is_write) {
                node->insert_or_assign(name, value);
            } else if (node && node->get(name)) {
                value = node->get(name)->as<T>()->get();
            }

            return *this;
        }

        Cfg& end_section()
        {
            return *cfg;
        }

    private:
        Section(Cfg* _cfg, toml::table* _node, bool _is_write)            
            : cfg(_cfg)
            , node(_node)
            , is_write(_is_write)
        {
        }

        Cfg* cfg;
        toml::table* node;
        bool is_write;
    };

    Cfg(const char* _filename, bool _is_write)
        : is_write(_is_write)
        , filename(_filename)
        , data()
    {
        if (!is_write) {
            this->data = toml::parse_file(_filename);
        }
    }

    void run()
    {
        if (is_write) {
            std::ofstream outfile(filename);
            outfile << data;
        }
    }

    Section begin_global_section() {
        return Section(this, &data, is_write);
    }

    Section begin_section(const std::string& name) {
        if (is_write) {
            data.insert_or_assign(name, toml::table());
        }

        return Section(this, data[name].as_table(), is_write);

    }

private:
    toml::table data;
    const char *filename;
    bool is_write;
};

Cfg parse(const char* filename)
{
    return Cfg(filename, false);
}
Cfg write(const char* filename)
{
    return Cfg(filename, true);
}


}
