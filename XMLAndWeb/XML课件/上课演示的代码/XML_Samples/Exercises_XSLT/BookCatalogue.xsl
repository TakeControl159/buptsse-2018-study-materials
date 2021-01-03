<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl" result-ns="html">
    <xsl:template match="/">
            <HTML>
            <HEAD>
            <TITLE>Book Catalogue</TITLE>
            </HEAD>
            <BODY>
                <xsl:apply-templates/>
            </BODY>
            </HTML>
    </xsl:template>
    <xsl:template match="BookCatalogue">
          mark wu  I am at BookCatalogue.  QQQ Processing its children now.<br/>
            <xsl:apply-templates/>
    </xsl:template>
    <xsl:template match="Book">
            I am at Book.  Processing its children now.<br/>
            <xsl:apply-templates/>
    </xsl:template>
    <xsl:template match="Title">
            I am at Title.  Here's the title:<br/>
            <xsl:apply-templates/><br/>
    </xsl:template>
    <xsl:template match="Author">
            I am at Author.  Here's the author's name:<br/>
            <xsl:apply-templates/><br/>
    </xsl:template>
    <xsl:template match="Date">
            I am at Date.  Here's the date:<br/>
            <xsl:apply-templates/><br/>
    </xsl:template>
    
    <xsl:template match="ISBN">
            I am at ISBN.  Here's the ISBN:<br/>
            <xsl:apply-templates/><br/>
    </xsl:template> 
    <xsl:template match="Publisher">
            I am at Publisher.  Here's the publisher:<!--<br/>-->
            <xsl:apply-templates/><br/>
    </xsl:template> 
    <xsl:template match="text()">
           <xsl:value-of select="."/>
    </xsl:template>
</xsl:stylesheet>
