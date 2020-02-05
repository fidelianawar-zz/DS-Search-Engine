# DS-Search-Engine
Final Semester Project

On a partner team, created a search engine in C++ that parses through a law corpus of 35,000+ documents. 
The engine's main features include document parser/processor, query processor, search processor, and ranking processor.

The user enters a search query, and any documents that satisfy that query are returned to the user ordered by relevance.
We implemented functionality to handle simple prefix Boolean queries entered by the user such as AND, OR, NOT and ranked results by term frequency – inverse document frequency (td-idf).

Custom implementation of:
AVL Tree, HashTable (with collisions handled by separate chaining), and inverted file index.
The inverted file index relates each unique word from the corpus to the document(s) in which it appears and allows for efficient execution of a query to quickly determine in which documents a particular query term appears.

UI includes Maintanence Mode and Interactive Mode.
Maintenance Mode allows the user to: add opinions to the index by supplying the path to a folder containing new opinions, clear the index completely, and parse the corpus and populate index
Interactive Mode allows user to: indicate if they want the index loaded into an AVL structure or a hash table structure (if a persisted index exists), enter a properly formatted Boolean query, choose one of the opinions from the result set above and have the first ~300 words of the opinion printed, find logistics of total number of opinions indexed, average number of words indexed per opinion (after removal of stop words), top 50 most frequent words (after removal of stop words).

