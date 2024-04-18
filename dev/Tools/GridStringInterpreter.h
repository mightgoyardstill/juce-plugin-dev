#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

namespace tools
{
class GridStringInterpreter
{
    juce::Grid grid;

    void parseLayout(const juce::String& gridLayout)
    {
        juce::StringArray lines;
        lines.addLines(gridLayout);

        for (const auto& line : lines)
        {
            if (line.contains("grid-template-columns:"))
                parseTrack(line, true); // true for columns
            else if (line.contains("grid-template-rows:"))
                parseTrack(line, false); // false for rows
            else if (line.contains("grid-template-areas:"))
                parseArea(line, lines);
            else if (line.contains("grid-gap:"))
                parseGap(line);
        }
    }

    void parseTrack(const juce::String& line, bool isColumn)
    {
        auto values = extractValuesFromLine(line);
        juce::Array<juce::Grid::TrackInfo> trackInfos;

        for (const auto& value : values)
        {
            if (value.contains("fr"))
            {
                auto size = static_cast<unsigned long long>(std::round(value.getDoubleValue()));
                trackInfos.add(juce::Grid::TrackInfo(juce::Grid::Fr(size)));
            }
            else if (value.contains("px"))
            {
                auto size = static_cast<float>(value.getDoubleValue());
                trackInfos.add(juce::Grid::TrackInfo(juce::Grid::Px(size)));
            }
        }

        if (isColumn)
            grid.templateColumns.swapWith(trackInfos);
        else
            grid.templateRows.swapWith(trackInfos);
    }

    void parseArea(const juce::String& line, const juce::StringArray& lines)
    {
        juce::String areaDefinition = line.fromFirstOccurrenceOf(":", false, false).trim();
        int nextLineIndex = lines.indexOf(line) + 1;

        while (nextLineIndex < lines.size() && !lines[nextLineIndex].contains(";"))
        {
            areaDefinition += " " + lines[nextLineIndex].trim();
            nextLineIndex++;
        }

        if (areaDefinition.contains(";"))
            areaDefinition = areaDefinition.upToLastOccurrenceOf(";", false, true);
        else if (nextLineIndex < lines.size())
            areaDefinition += " " + lines[nextLineIndex].upToLastOccurrenceOf(";", false, true);

        juce::String currentArea;
        juce::StringArray tempAreas;

        bool inQuote = false;
        juce::juce_wchar quoteChar = 0;

        for (juce::juce_wchar character : areaDefinition)
        {
            if ((character == '"' || character == '\'') && (!inQuote || character == quoteChar))
            {
                inQuote = !inQuote;
                quoteChar = inQuote ? character : 0;
                
                if (!inQuote && !currentArea.isEmpty())
                {
                    tempAreas.add(currentArea);
                    currentArea.clear();
                }
            }
            else if (inQuote)
                currentArea += character;
        }

        grid.templateAreas.swapWith(tempAreas);
    }

    void parseGap(const juce::String& line)
    {
        auto values = extractValuesFromLine(line);

        for (const auto& value : values)
        {
            if (value.contains("px"))
                grid.setGap(juce::Grid::Px(value.getFloatValue()));
        }
    }

    juce::StringArray extractValuesFromLine(const juce::String& line)
    {
        auto valueString = line.fromFirstOccurrenceOf(":", false, false).trim();
        return juce::StringArray::fromTokens(valueString, " ", "");
    }

    void addComponents(const std::initializer_list<std::pair<juce::Component*, juce::String>>& components)
    {
        grid.items.clear();

        for (const auto& [comp, area] : components)
            grid.items.add(juce::GridItem(comp).withArea(area));
    }

public:
    void setLayout (const juce::String& gridLayout, 
                    const std::initializer_list<std::pair<juce::Component*, juce::String>>& components)
    {
        addComponents(components);
        parseLayout(gridLayout);
    }

    void performLayout (const juce::Rectangle<int>& bounds) 
    {
        grid.performLayout(bounds);
    }
};
} // namespace tools