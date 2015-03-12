# 0) Preface #
Where possible and appropriate we will use already created OPEN standards (especially FreeDesktop).

# 1) Colours #

All colours are loaded from ~/.sope/colours.xml first, and if that doesn't exist or doesn't contain all the needed colours, get the rest from /etc/sope/colours.xml (this path can be added to with the SOPE\_SETTINGS\_PATH environment variable, in which case the first things searched will be everything in $SOPE\_SETTINGS\_PATH/colours.xml). If none of these exist, fall back on defaults.

## 1.1) Background ##
Default Colour: RGBA(170, 204, 238, 255)

```
<section name="background">
<colour r="170" g="204" b="238" a="255">BGColour</colour>
</section>
```


## 1.2) Widgets ##
Default BGColour: RGBA(1, 151, 253, 255)

Defualt FanColour: RGBA(1, 205, 253, 255)
Blurred

```
<section name="widgets">
<colour r="1" g="151" b="253" a="255">BGColour</colour>
<colour r="1" g="205" b="253" a="255">FanColour</colour>
</section>
```

# 2) System settings #

These are settings pertaining to the whole Soap insallation that will always be the same throughout the whole of the installation. There aren't many of these, and changing them is not recommended. These are saved in SOPE\_SETTINGS\_PATH/system.xml (if it exists, /etc/sope/system.xml if and only if it doesn't). They cannot be overridden by single users (since they are designed to be the same in one installation).

## 2.1) Names ##

The name of the Sope installation and its version, and finally anything to append to the end (for specific "editions").

Default project\_name: Project Sope (for now)

Default version: The version number of the installation.

Default append: Nothing (NULL string)

```
<section name="names">
<setting value="Project Sope">project_name</setting>
<setting value="0.0000001 alpha">version</setting>
<setting value="">append</setting>
</section>
```

# 3) Language #
We will use british english when coding but use the tr() function to insure all strings are easily translatable.

TBC