
namespace D2HD 
{
	class D2HDResolution 
	{
	public:
		D2HDResolution(const int width, const int height);
		int getWidth() const;
		int getHeight() const;

		bool operator==(const D2HD::D2HDResolution& other) const;

		static std::vector<D2HDResolution>& getResolutions();

	private:
		static std::vector<D2HDResolution> resolutions;
		static void removeNonStandardResolutions();

		int width;
		int height;
	};
}


