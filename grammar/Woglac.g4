grammar Woglac;

module:
	(content+=statement)* EOF;

statement:
	pragmaStatement
	| paramDefinition
	| biomeParamDefinition
	| paramSetStatement
	| biomeConditionStatement
	| variableDefinition
	| ruleExpansionStatement
	| scope
	| componentNodeStatement
	| componentBlockStatement
	| componentAreaStatement
	| structureConditionStatement
	| componentIncludeStatement;

scope:
	extend='extend'? type= ('namespace' | 'rule' | 'component' | 'biome') id= extendedIdentifier contentOrSemicolon
	| '{' content+= statement* '}';

contentOrSemicolon:
	'{' content+= statement* '}'
	| ';';

pragmaStatement:
	'pragma' id= extendedIdentifier ('=' (valLit= literalExpression | valId= Identifier))? ';';

variableDefinition:
	exportFlag='export'? type=Type id=extendedIdentifier '=' val=expression ';';

paramDefinition:
	(targetType=('rule' | 'component') target=extendedIdentifier?)? 'param' type=Type id=Identifier ('?=' defaultValue=expression)? ';';

biomeParamDefinition:
	'biome' 'param' type=Type id=extendedIdentifier '?=' defaultValue=expression ';';

paramSetStatement:
	(targetType=('biome' | 'rule' | 'component') target=extendedIdentifier)? 'param' param=extendedIdentifier '=' value=expression ';';

biomeConditionStatement:
	('biome' target=extendedIdentifier?)? 'condition' param=extendedIdentifier '=' mean=NumericLiteral '+-' dev=NumericLiteral ';';

structureConditionStatement:
	(targetType=('component' | 'rule') target=extendedIdentifier?)? 'condition' cond=expression ';';

ruleExpansionStatement:
	'rule' target=extendedIdentifier? '->' (expansionTarget=extendedIdentifier ('::' node=Identifier)? | 'void') ('!' priority=NumericLiteral)? (':' probabilityRatio=NumericLiteral)? content=contentOrSemicolon;

componentNodeStatement:
	('component' target=extendedIdentifier)? 'node' pos=positionExpression cmn=componentNodeStatementCommonPart;

componentNodeStatementCommonPart:
	prop=componentNodePropertiesSection? group=Identifier? ('->' rule_=extendedIdentifier)? contentOrSemicolon;

componentNodePropertiesSection:
	'(' notAdjacent='='? horizontalEdge='|'? verticalEdge='-'? ori=componentNodeOrientationExpression (ori2=componentNodeOrientationExpression)? ')';

componentNodeOrientationExpression:
	dir=Identifier sign=('+' | '-');

componentAreaStatement:
	('component' target=extendedIdentifier)? 'area' startPos=positionExpression endPos=positionExpression ('(' canOverlap='#'? mustOverlap='!'? isVirtual='?'? ')')? name=Identifier? ';';

componentBlockStatement:
	('component' target=extendedIdentifier)? 'block' startPos=positionExpression endPos=positionExpression? '=' val=expression ';';

componentIncludeStatement:
	'component' 'include'  file=StringLiteral '{' content+= componentIncludeStatementParam* '}';

componentIncludeStatementParam:
	block= componentIncludeStatementBlockParam
	| node= componentIncludeStatementNodeParam;

componentIncludeStatementBlockParam:
	id=NumericLiteral '->' 'block' val=expression ';';
componentIncludeStatementNodeParam:
	id=NumericLiteral '->' 'node' com=componentNodeStatementCommonPart;

positionExpression:
	'(' (x= expression ',' y= expression ',' z= expression | vec= expression) ')';

expression:
	e= ternaryExpression;

parentExpression:
	'(' e= expression ')';
ternaryExpression:
	base= logicalExpression
	| condition= logicalExpression '?' thenBranch= logicalExpression? ':' elseBranch= ternaryExpression;
logicalExpression:
	a= andExpression
	| o= orExpression;
andExpression:
	base= comparisonExpression
	| left= andExpression '&&' right= comparisonExpression;
orExpression:
	base= comparisonExpression
	| left= orExpression '||' right= comparisonExpression;
comparisonExpression:
	base= addExpression
	| left= addExpression op= ComparisonOp right= addExpression;
addExpression:
	base= multExpression
	| left= addExpression op= ('+' | '-') right= multExpression;
multExpression:
	base= unaryExpression
	| left= multExpression op= MultOp right= unaryExpression;
unaryExpression:
	base= inlineFunctionCallExpression
	| op=('+' | '-') arg= inlineFunctionCallExpression
	| op= '!' arg= inlineFunctionCallExpression;
inlineFunctionCallExpression:
	base= atomicExpression
	| arg1=inlineFunctionCallExpression '::' id=Identifier args=arugmentListExpression;
atomicExpression:
	funcCall= functionCallExpression
	| lit= literalExpression
	| par= parentExpression
	| bio= biomeParamExpression
	| id= extendedIdentifier;

arugmentListExpression:
	'(' (args+= expression ( ',' args+= expression)* ','?)? ')';

biomeParamExpression:
	'biome' '(' param= extendedIdentifier ',' method= Identifier (',' params+= expression)* ')';
functionCallExpression:
	id= Identifier args= arugmentListExpression;

extendedIdentifier:
	id+= Identifier ('.' id+= Identifier)*;
literalExpression:
	('#' | '~')? num= NumericLiteral
	| block= BlockLiteral
	| bool_= BoolLiteral
	| string= StringLiteral;

LineComment:
	'//' ~('\r' | '\n')* -> channel(HIDDEN);
BlockComment:
	'/*' (BlockComment | .)*? '*/' -> channel(HIDDEN);
Whitespace:
	[ \t\n\r] -> channel(HIDDEN);

Type:
	'Block'
	| 'Float'
	| 'Float2'
	| 'Float3'
	| 'Bool'
	| 'Bool2'
	| 'Bool3'
	| 'Rule'
	| 'ComponentNode';
BlockLiteral:
	'block.' [a-zA-Z.0-9]+;
ComparisonOp:
	'<'
	| '<='
	| '>'
	| '>='
	| '=='
	| '!=';
BoolLiteral:
	'true'
	| 'false';
StringLiteral:
	'"' (~'"')+ '"';
MultOp:
	'*'
	| '/';

Identifier:
	[a-zA-Z_][a-zA-Z_0-9]*;
NumericLiteral:
	'-'? ([0-9]+ ('.' [0-9]+)? | '.' [0-9]+);