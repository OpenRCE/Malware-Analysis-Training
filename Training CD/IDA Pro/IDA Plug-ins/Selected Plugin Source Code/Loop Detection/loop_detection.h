#ifndef _LOOP_DETECTION_H
#define _LOOP_DETECTION_H


#include <ida.hpp>
#include <idp.hpp>
#include <bytes.hpp>
#include <expr.hpp>
#include <frame.hpp>
#include <gdl.hpp>
#include <kernwin.hpp>
#include <loader.hpp>
#include <md5.h>
#include <name.hpp>
#include <ua.hpp>
#include <struct.hpp>
#include "function_analyzer.h"
#include "color_palette.h"
#define TRUE 1
#define FALSE 0

class loop_detection : public function_analyzer
{
public:
	
	//functions that implement options
	void find_recursive_functions();
	void highlight_codes();
	void highlight_functions();
	//constructors/destructors
	loop_detection(ea_t ea);
	loop_detection(int fid);
	loop_detection(func_t * fptr);
	virtual ~loop_detection();



	//graph helper functions
	int is_end_loop(ea_t ea);
	int is_start_loop(ea_t ea);
	int add_end_loop(ea_t ea);
	int add_start_loop(ea_t ea);
	int is_loop(ea_t ea);
	int add_loop(ea_t ea);

	//loop detection functions
	void find_loops();
	int find_loop(ea_t master, ea_t slave);
	int is_path_to(ea_t from, ea_t to, ea_t avoid);
	int is_valid_node(ea_t ea);
	ea_t is_fragmented_head(ea_t head);
	int is_path_to(ea_t from, ea_t to);
	int find_natural_loop(ea_t master, ea_t slave);
	void find_natural_loops();

	//virtual functions
	 virtual void run_analysis();
	 virtual void graph();
	 virtual void constructor();
	
	//our setters
	void set_graph(unsigned short choice)						{  graph_loop			= choice;	}
	void set_higlight_function(unsigned short choice)			{ highlight_function	= choice;	}
	void set_output_stack(unsigned short choice)				{ output_stack			= choice;	}
	void set_highlight_code(unsigned short choice)				{ highlight_code		= choice;	}
	void set_natural_loops(unsigned short choice)				{ natural_loops			= choice;	}
	void set_recursive_function(unsigned short choice)			{ recursive_function	= choice;	}
	void set_verbose_output(unsigned short choice)				{ verbose_output		= choice;	}
	void set_auto_comment(unsigned short choice)				{ auto_comment			= choice;	}
	
	//
	// our getters
	//
	unsigned short	 get_graph()								{ return graph_loop;				}
	unsigned short	 get_highlight_function()					{ return highlight_function;		}
	unsigned short	 get_output_stack()							{ return output_stack;				}
	unsigned short	 get_highlight_code()						{ return highlight_code;			}
	unsigned short  get_natural_loops()							{ return natural_loops;				}
	unsigned short  get_recursive_function()					{ return recursive_function;		}
	unsigned short  get_verbose_output()						{ return verbose_output;		}
	unsigned short  get_auto_comment()							{ return auto_comment;		}


private:
	
	ea_t		  *loops;
	ea_t		  *start_loops;
	ea_t		  *end_loops;
	ea_t		   entry_point;
	int			  num_loops;
	int			  num_start_loops;
	int			  num_end_loops;

	//options
	 unsigned short graph_loop;			
	 unsigned short highlight_function;	
	 unsigned short output_stack;		
	 unsigned short highlight_code;		
	 unsigned short natural_loops;			
	 unsigned short recursive_function;
	 unsigned short verbose_output;
	 unsigned short auto_comment;

};

#endif // !defined(AFX_LOOP_DETECTION_H__7E72A5B8_AFC0_4CFF_BF23_8684885E022F__INCLUDED_)
