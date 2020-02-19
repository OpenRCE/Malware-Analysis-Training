<?xml version="1.0" encoding="iso-8859-1"?>
<!--
    (c) by Christian Foltin, 2005
    This file is licensed under the GPL.
-->
<xsl:stylesheet version="1.0" xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:office="http://openoffice.org/2000/office"
	xmlns:style="http://openoffice.org/2000/style"
	xmlns:text="http://openoffice.org/2000/text"
	xmlns:table="http://openoffice.org/2000/table"
	xmlns:draw="http://openoffice.org/2000/drawing"
	xmlns:fo="http://www.w3.org/1999/XSL/Format"
	xmlns:xlink="http://www.w3.org/1999/xlink"
	xmlns:number="http://openoffice.org/2000/datastyle"
	xmlns:svg="http://www.w3.org/2000/svg"
	xmlns:chart="http://openoffice.org/2000/chart"
	xmlns:dr3d="http://openoffice.org/2000/dr3d"
	xmlns:math="http://www.w3.org/1998/Math/MathML"
	xmlns:form="http://openoffice.org/2000/form"
	xmlns:script="http://openoffice.org/2000/script">
	<xsl:output method="xml" version="1.0" indent="yes" encoding="iso-8859-1"
		doctype-public="-//OpenOffice.org//DTD OfficeDocument 1.0//EN"
		doctype-system="office.dtd" omit-xml-declaration="no"/>
	<xsl:strip-space elements="*"/>
	
	<xsl:template match="map">
		<office:document-content xmlns:office="http://openoffice.org/2000/office"
			xmlns:style="http://openoffice.org/2000/style"
			xmlns:text="http://openoffice.org/2000/text"
			xmlns:table="http://openoffice.org/2000/table"
			xmlns:draw="http://openoffice.org/2000/drawing"
			xmlns:fo="http://www.w3.org/1999/XSL/Format"
			xmlns:xlink="http://www.w3.org/1999/xlink"
			xmlns:number="http://openoffice.org/2000/datastyle"
			xmlns:svg="http://www.w3.org/2000/svg"
			xmlns:chart="http://openoffice.org/2000/chart"
			xmlns:dr3d="http://openoffice.org/2000/dr3d"
			xmlns:math="http://www.w3.org/1998/Math/MathML"
			xmlns:form="http://openoffice.org/2000/form"
			xmlns:script="http://openoffice.org/2000/script" office:class="text"
			office:version="1.0">
			<office:script/>
			<office:font-decls>
				<style:font-decl style:name="Tahoma1"
					fo:font-family="Tahoma, Lucidasans, &apos;Lucida Sans&apos;, &apos;Arial Unicode MS&apos;"/>
				<style:font-decl style:name="HG Mincho Light J"
					fo:font-family="&apos;HG Mincho Light J&apos;, &apos;MS Mincho&apos;, &apos;HG Mincho J&apos;, &apos;HG Mincho L&apos;, &apos;HG Mincho&apos;, Mincho, &apos;MS PMincho&apos;, &apos;HG Mincho Light J&apos;, &apos;MS Gothic&apos;, &apos;HG Gothic J&apos;, &apos;HG Gothic B&apos;, &apos;HG Gothic&apos;, Gothic, &apos;MS PGothic&apos;, &apos;Andale Sans UI&apos;, &apos;Arial Unicode MS&apos;, &apos;Lucida Sans Unicode&apos;, Tahoma"
					style:font-pitch="variable"/>
				<style:font-decl style:name="Nimbus Sans L1"
					fo:font-family="&apos;Nimbus Sans L&apos;"
					style:font-pitch="variable"/>
				<style:font-decl style:name="Tahoma"
					fo:font-family="Tahoma, Lucidasans, &apos;Lucida Sans&apos;, &apos;Arial Unicode MS&apos;"
					style:font-pitch="variable"/>
				<style:font-decl style:name="Nimbus Roman No9 L"
					fo:font-family="&apos;Nimbus Roman No9 L&apos;"
					style:font-family-generic="roman"
					style:font-pitch="variable"/>
				<style:font-decl style:name="Nimbus Sans L"
					fo:font-family="&apos;Nimbus Sans L&apos;"
					style:font-family-generic="swiss"
					style:font-pitch="variable"/>
			</office:font-decls>
			<office:automatic-styles>
				<style:style style:name="P1" style:family="paragraph"
					style:parent-style-name="Heading">
					<style:properties fo:text-align="center"
						style:justify-single-word="false"/>
				</style:style>
				<style:style style:name="P2" style:family="paragraph"
					style:parent-style-name="Contents 1">
					<style:properties>
						<style:tab-stops>
							<style:tab-stop style:position="17.59cm"
								style:type="right" style:leader-char="."/>
						</style:tab-stops>
					</style:properties>
				</style:style>
				<style:style style:name="P3" style:family="paragraph"
					style:parent-style-name="Contents 2">
					<style:properties>
						<style:tab-stops>
							<style:tab-stop style:position="17.59cm"
								style:type="right" style:leader-char="."/>
						</style:tab-stops>
					</style:properties>
				</style:style>
				<style:style style:name="P4" style:family="paragraph"
					style:parent-style-name="Contents 3">
					<style:properties>
						<style:tab-stops>
							<style:tab-stop style:position="17.59cm"
								style:type="right" style:leader-char="."/>
						</style:tab-stops>
					</style:properties>
				</style:style>
				<style:style style:name="P5" style:family="paragraph"
					style:parent-style-name="Contents 4">
					<style:properties>
						<style:tab-stops>
							<style:tab-stop style:position="17.59cm"
								style:type="right" style:leader-char="."/>
						</style:tab-stops>
					</style:properties>
				</style:style>
				<style:style style:name="P6" style:family="paragraph"
					style:parent-style-name="Contents 5">
					<style:properties>
						<style:tab-stops>
							<style:tab-stop style:position="17.59cm"
								style:type="right" style:leader-char="."/>
						</style:tab-stops>
					</style:properties>
				</style:style>
				<style:style style:name="P7" style:family="paragraph"
					style:parent-style-name="Contents 6">
					<style:properties>
						<style:tab-stops>
							<style:tab-stop style:position="17.59cm"
								style:type="right" style:leader-char="."/>
						</style:tab-stops>
					</style:properties>
				</style:style>
				<style:style style:name="P8" style:family="paragraph"
					style:parent-style-name="Text body">
					<style:properties fo:font-weight="normal"
						style:font-weight-asian="normal"
						style:font-weight-complex="normal"/>
				</style:style>
				<style:style style:name="P9" style:family="paragraph"
					style:parent-style-name="Text body">
					<style:properties fo:font-style="italic"
						style:text-underline="single"
						style:text-underline-color="font-color"
						fo:font-weight="normal" style:font-style-asian="italic"
						style:font-weight-asian="normal"
						style:font-style-complex="italic"
						style:font-weight-complex="normal"/>
				</style:style>
				<style:style style:name="P10" style:family="paragraph"
					style:parent-style-name="Text body">
					<style:properties fo:font-style="italic"
						style:text-underline="single"
						style:text-underline-color="font-color"
						fo:font-weight="bold" style:font-style-asian="italic"
						style:font-weight-asian="bold"
						style:font-style-complex="italic"
						style:font-weight-complex="bold"/>
				</style:style>
				<style:style style:name="P11" style:family="paragraph"
					style:parent-style-name="Text body">
					<style:properties fo:color="#ff0000" fo:font-weight="normal"
						style:font-weight-asian="normal"
						style:font-weight-complex="normal"/>
				</style:style>
				<style:style style:name="P101" style:family="paragraph"
					style:parent-style-name="Heading 1"
					style:list-style-name="L1"/>
				<style:style style:name="P102" style:family="paragraph"
					style:parent-style-name="Heading 2"
					style:list-style-name="L1"/>
				<style:style style:name="P103" style:family="paragraph"
					style:parent-style-name="Heading 3"
					style:list-style-name="L1"/>
				<style:style style:name="P104" style:family="paragraph"
					style:parent-style-name="Heading 4"
					style:list-style-name="L1"/>
				<style:style style:name="P105" style:family="paragraph"
					style:parent-style-name="Heading 5"
					style:list-style-name="L1"/>
				<style:style style:name="P106" style:family="paragraph"
					style:parent-style-name="Heading 6"
					style:list-style-name="L1"/>
				<style:style style:name="P107" style:family="paragraph"
					style:parent-style-name="Heading 7"
					style:list-style-name="L1"/>
				<style:style style:name="P108" style:family="paragraph"
					style:parent-style-name="Heading 8"
					style:list-style-name="L1"/>
				<style:style style:name="P109" style:family="paragraph"
					style:parent-style-name="Heading 9"
					style:list-style-name="L1"/>
				<style:style style:name="T1" style:family="text">
					<style:properties fo:color="#ff0000"/>
				</style:style>
				<style:style style:name="T2" style:family="text">
					<style:properties fo:font-weight="bold"
						style:font-weight-asian="bold"
						style:font-weight-complex="bold"/>
				</style:style>
				<style:style style:name="T3" style:family="text">
					<style:properties fo:font-style="italic"
						style:font-style-asian="italic"
						style:font-style-complex="italic"/>
				</style:style>
				<style:style style:name="T4" style:family="text">
					<style:properties style:text-underline="single"
						style:text-underline-color="font-color"/>
				</style:style>
				<style:style style:name="T5" style:family="text">
					<style:properties fo:font-style="italic" fo:font-weight="bold"
						style:font-style-asian="italic"
						style:font-weight-asian="bold"
						style:font-style-complex="italic"
						style:font-weight-complex="bold"/>
				</style:style>
				<style:style style:name="T6" style:family="text">
					<style:properties style:text-underline="single"
						style:text-underline-color="font-color"
						fo:font-weight="bold" style:font-weight-asian="bold"
						style:font-weight-complex="bold"/>
				</style:style>
				<style:style style:name="T7" style:family="text">
					<style:properties fo:font-style="italic"
						style:text-underline="single"
						style:text-underline-color="font-color"
						fo:font-weight="normal" style:font-style-asian="italic"
						style:font-weight-asian="normal"
						style:font-style-complex="italic"
						style:font-weight-complex="normal"/>
				</style:style>
				<style:style style:name="T8" style:family="text">
					<style:properties fo:font-style="italic"
						style:text-underline="single"
						style:text-underline-color="font-color"
						fo:font-weight="bold" style:font-style-asian="italic"
						style:font-weight-asian="bold"
						style:font-style-complex="italic"
						style:font-weight-complex="bold"/>
				</style:style>
				<style:style style:name="fr1" style:family="graphics"
					style:parent-style-name="Frame">
					<style:properties fo:margin-left="0cm" fo:margin-right="0cm"
						fo:margin-top="0cm" fo:margin-bottom="0cm"
						style:wrap="none" style:vertical-pos="from-top"
						style:vertical-rel="paragraph"
						style:horizontal-pos="from-left"
						style:horizontal-rel="paragraph" fo:padding="0cm"
						fo:border="none"/>
				</style:style>
				<style:style style:name="fr2" style:family="graphics"
					style:parent-style-name="Graphics">
					<style:properties fo:margin-left="0cm" fo:margin-right="0cm"
						fo:margin-top="0cm" fo:margin-bottom="0cm"
						style:run-through="foreground" style:wrap="none"
						style:vertical-pos="from-top"
						style:vertical-rel="paragraph-content"
						style:horizontal-pos="from-left"
						style:horizontal-rel="paragraph-content" fo:padding="0cm"
						fo:border="none" style:shadow="none" style:mirror="none"
						fo:clip="rect(0cm 0cm 0cm 0cm)" draw:luminance="0%"
						draw:contrast="0%" draw:red="0%" draw:green="0%"
						draw:blue="0%" draw:gamma="1" draw:color-inversion="false"
						draw:transparency="0%" draw:color-mode="standard"/>
				</style:style>
				
				<text:list-style style:name="L2">
					<text:list-level-style-bullet text:level="1"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix="." text:bullet-char="¥">
						<style:properties text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
					<text:list-level-style-bullet text:level="2"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix="." text:bullet-char="¥">
						<style:properties text:space-before="0.501cm"
							text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
					<text:list-level-style-bullet text:level="3"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix=")" text:bullet-char="¥">
						<style:properties text:space-before="1cm"
							text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
					<text:list-level-style-bullet text:level="4"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix=" " text:bullet-char="¥">
						<style:properties text:space-before="1.501cm"
							text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
					<text:list-level-style-bullet text:level="5"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix=" " text:bullet-char="¥">
						<style:properties text:space-before="2cm"
							text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
					<text:list-level-style-bullet text:level="6"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix=" " text:bullet-char="¥">
						<style:properties text:space-before="2.501cm"
							text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
					<text:list-level-style-bullet text:level="7"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix=" " text:bullet-char="¥">
						<style:properties text:space-before="3.001cm"
							text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
					<text:list-level-style-bullet text:level="8"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix=" " text:bullet-char="¥">
						<style:properties text:space-before="3.502cm"
							text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
					<text:list-level-style-bullet text:level="9"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix=" " text:bullet-char="¥">
						<style:properties text:space-before="4.001cm"
							text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
					<text:list-level-style-bullet text:level="10"
						text:style-name="Bullet Symbols" style:num-prefix=" "
						style:num-suffix=" " text:bullet-char="¥">
						<style:properties text:space-before="4.502cm"
							text:min-label-width="0.499cm"
							style:font-name="StarSymbol"/>
					</text:list-level-style-bullet>
				</text:list-style>
				
				<style:style style:name="Sect1" style:family="section">
					<style:properties fo:background-color="transparent">
						<style:columns fo:column-count="0" fo:column-gap="0cm"/>
						<style:background-image/>
					</style:properties>
				</style:style>
				<style:style style:name="Sect2" style:family="section">
					<style:properties>
						<style:columns fo:column-count="0" fo:column-gap="0cm"/>
					</style:properties>
				</style:style>
				<text:list-style style:name="L1">
					<text:list-level-style-number text:level="1"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1">
						<style:properties text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
					<text:list-level-style-number text:level="2"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1"
						text:display-levels="2">
						<style:properties text:space-before="0.501cm"
							text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
					<text:list-level-style-number text:level="3"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1"
						text:display-levels="3">
						<style:properties text:space-before="1cm"
							text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
					<text:list-level-style-number text:level="4"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1"
						text:display-levels="4">
						<style:properties text:space-before="1.501cm"
							text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
					<text:list-level-style-number text:level="5"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1"
						text:display-levels="5">
						<style:properties text:space-before="2cm"
							text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
					<text:list-level-style-number text:level="6"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1"
						text:display-levels="6">
						<style:properties text:space-before="2.501cm"
							text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
					<text:list-level-style-number text:level="7"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1"
						text:display-levels="7">
						<style:properties text:space-before="3.001cm"
							text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
					<text:list-level-style-number text:level="8"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1"
						text:display-levels="8">
						<style:properties text:space-before="3.502cm"
							text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
					<text:list-level-style-number text:level="9"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1"
						text:display-levels="9">
						<style:properties text:space-before="4.001cm"
							text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
					<text:list-level-style-number text:level="10"
						text:style-name="Numbering Symbols" style:num-prefix=" "
						style:num-suffix=" " style:num-format="1"
						text:display-levels="10">
						<style:properties text:space-before="4.502cm"
							text:min-label-width="0.499cm"/>
					</text:list-level-style-number>
				</text:list-style>
			</office:automatic-styles>
			<office:body>
				<text:sequence-decls>
					<text:sequence-decl text:display-outline-level="0"
						text:name="Illustration"/>
					<text:sequence-decl text:display-outline-level="0"
						text:name="Table"/>
					<text:sequence-decl text:display-outline-level="0"
						text:name="Text"/>
					<text:sequence-decl text:display-outline-level="0"
						text:name="Drawing"/>
				</text:sequence-decls>
				
				<xsl:apply-templates select="node"/>
			</office:body>
		</office:document-content>
	</xsl:template>
	
	<xsl:template match="node">
		<xsl:variable name="depth">
			<xsl:apply-templates select=".." mode="depthMesurement"/>
		</xsl:variable>
		<xsl:choose>
			<xsl:when test="$depth=0">
				<text:p text:style-name="P1">
					<xsl:value-of select="@TEXT"/>
				</text:p>
				
				<xsl:apply-templates select="hook|@LINK"/>
				<xsl:apply-templates select="node"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:choose>
					<xsl:when test="ancestor::node[@FOLDED='true']">
						<xsl:apply-templates select=".." mode="childoutputUnordered">
							<xsl:with-param name="nodeText">
								<text:p text:style-name="Standard">
									<xsl:value-of select="@TEXT"/>
								</text:p>	
							</xsl:with-param>
						</xsl:apply-templates>						
					</xsl:when>
					<xsl:otherwise>
						<xsl:apply-templates select=".."
							mode="childoutputOrdered">
							<xsl:with-param name="nodeText">
								<xsl:element name="text:h" namespace="text">
									<xsl:attribute name="text:style-name"
										namespace="text">
										<xsl:text>P</xsl:text><xsl:value-of
											select="$depth+100"/>
									</xsl:attribute>
									<xsl:attribute name="text:level"
										namespace="text"><xsl:value-of
											select="$depth"/></xsl:attribute>
									<xsl:value-of select="@TEXT"/>
								</xsl:element>
							</xsl:with-param>
						</xsl:apply-templates>
					</xsl:otherwise>
				</xsl:choose>
				<xsl:apply-templates select="hook|@LINK"/>
				<xsl:apply-templates select="node"/>
			</xsl:otherwise>
		</xsl:choose>
		
	</xsl:template>
	
	<xsl:template match="hook"/>
	
	<xsl:template match="hook[@NAME='accessories/plugins/NodeNote.properties']">
		<xsl:choose>
			<xsl:when test="./text">
				<text:p text:style-name="Standard">
					<xsl:value-of select="./text"/>
				</text:p>
			</xsl:when>
		</xsl:choose>
	</xsl:template>
	
	<xsl:template match="node" mode="childoutputOrdered">
		<xsl:param name="nodeText"></xsl:param>
			<text:ordered-list text:style-name="L1"
				text:continue-numbering="true">
				<text:list-item>
					<xsl:apply-templates select=".." mode="childoutputOrdered">
						<xsl:with-param name="nodeText"><xsl:copy-of
								select="$nodeText"/></xsl:with-param>
					</xsl:apply-templates>
				</text:list-item>
			</text:ordered-list>
	</xsl:template>
	
	<xsl:template match="node" mode="childoutputUnordered">
		<xsl:param name="nodeText"></xsl:param>
				<text:unordered-list>
					<text:list-item>
						<xsl:apply-templates select=".." mode="childoutputUnordered">
							<xsl:with-param name="nodeText"><xsl:copy-of
									select="$nodeText"/></xsl:with-param>
						</xsl:apply-templates>
					</text:list-item>
				</text:unordered-list>
	</xsl:template>
	
	<xsl:template match="map" mode="childoutputOrdered">
		<xsl:param name="nodeText"></xsl:param>
		<xsl:copy-of select="$nodeText"/>
	</xsl:template>
	<xsl:template match="map" mode="childoutputUnordered">
		<xsl:param name="nodeText"></xsl:param>
		<xsl:copy-of select="$nodeText"/>
	</xsl:template>

	<xsl:template match="node" mode="depthMesurement">
        <xsl:param name="depth" select=" '0' "/>
        <xsl:apply-templates select=".." mode="depthMesurement">
                <xsl:with-param name="depth" select="$depth + 1"/>
        </xsl:apply-templates>
	</xsl:template>
	<xsl:template match="map" mode="depthMesurement">
        <xsl:param name="depth" select=" '0' "/>
		<xsl:value-of select="$depth"/>
	</xsl:template>

		
	<!-- Give links out. -->
	<xsl:template match="@LINK">
		<text:p text:style-name="Standard">
			<xsl:element name="text:a" namespace="text">
				<xsl:attribute namespace="xlink" name="xlink:type">simple</xsl:attribute>
				<xsl:attribute namespace="xlink" name="xlink:href"><xsl:value-of select="."/>
				</xsl:attribute>
				<xsl:value-of select="."/>
			</xsl:element>
		</text:p>
	</xsl:template>
	
</xsl:stylesheet>
