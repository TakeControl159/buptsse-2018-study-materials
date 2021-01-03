<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

    <xsl:variable name="lower" select="'abcdefghijklmnopqrstuvwxyz'" />
    <xsl:variable name="upper" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'" />

    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*" />
        </xsl:copy>
    </xsl:template>

    <xsl:template match="*">
        <xsl:variable name="prefix" select="name(namespace::*[. = namespace-uri(current())])" />

        <xsl:variable name="upperName" select="translate(local-name(), $lower, $upper )" />

        <xsl:variable name="newName">
            <xsl:choose>
                <xsl:when test="$prefix">
                    <xsl:value-of select="concat($prefix, ':', $upperName)" />
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="$upperName" />
                </xsl:otherwise>
            </xsl:choose>
      </xsl:variable>

      <xsl:element name="{$newName}" namespace="{namespace-uri(.)}">
          <xsl:copy-of select="namespace::*" />
          <xsl:apply-templates select="node()|@*" />
      </xsl:element>

  </xsl:template>

</xsl:stylesheet>

