namespace D2HD 
{
    class D2HDColor {
    public:
        D2HDColor(const unsigned char red, const unsigned char green,
            const unsigned char blue, const unsigned char tint);
        unsigned int getBGRFormat() const;
        unsigned int getRGBFormat() const;

        static D2HDColor createFromRGBFormat(const unsigned int color);
        static D2HDColor createFromRGBFormat(const std::string& color);
        static D2HDColor createFromRGBFormat(const std::wstring& color);

        static D2HDColor createFromBGRFormat(const unsigned int color);
        static D2HDColor createFromBGRFormat(const std::string& color);
        static D2HDColor createFromBGRFormat(const std::wstring& color);

    private:
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char tint;
    };
}