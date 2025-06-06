#include <hc_list_helpers.h>

template <class symbol_info> struct ST_node {
	ST_node(const ST<symbol_info> &r, const name_type &name, symbol_info *ip);
	ST<symbol_info> rest;
	name_type n;
	symbol_info *iptr;  // Todo: make this a refcounted pointer, or do so in haverfordCS::list
};
template <class symbol_info> ST_node<symbol_info>::ST_node(const ST<symbol_info> &r, const name_type &name, symbol_info *ip) : rest(r), n(name), iptr(ip)
{
    // C++ usage note, for Java programmers
	// The bit after the single ":" above initializes "n" with the value "name", etc.
	// It's a lot like putting "n = name;" in the body,
	//  but the latter would first build a null "n" and then re-define it,
	//  and we don't want to assume that "name_type" allows null definition.
}



// PUBLIC FUNCTIONS

template <class symbol_info> ST<symbol_info>::ST()
{
	head = 0;
}

template <class symbol_info> ST<symbol_info>::ST(const name_type &name, const symbol_info &info)
{
	head = new ST_node<symbol_info>(ST<symbol_info>(), name, new symbol_info(info));
}
template <class symbol_info> ST<symbol_info>::ST(std::pair<const name_type &, const symbol_info &> entry)
{
	head = new ST_node<symbol_info>(ST<symbol_info>(), entry.first, new symbol_info(entry.second));
}

template <class symbol_info> ST<symbol_info>::ST(std::list<std::pair<const name_type &, const symbol_info &>> entries)
{
    head = 0;
    for (auto entry: entries) { // "auto" deduces type automatically
        *this = FuseOneScope(ST(entry), *this);
    }
}

template <class symbol_info> ST<symbol_info> fuse(const ST<symbol_info> &s1, const ST<symbol_info> &s2)
{
	return merge_or_fuse(s1, s2, false);
}

template <class symbol_info> ST<symbol_info> merge(const ST<symbol_info> &inner, const ST<symbol_info> &outer)
{
	return merge_or_fuse(inner, outer, true);
}

template <class symbol_info> bool is_name_there(const name_type &look_for_me, const ST<symbol_info> &in_this_table)
{
	return in_this_table.check_for(look_for_me);
}


template <class symbol_info> symbol_info &lookup(const name_type &must_find_this, const ST<symbol_info> &in_this_table)
{
	const ST_node<symbol_info> *it = in_this_table.check_for(must_find_this);
	if (it == 0)
		throw undefined_symbol(must_find_this);
	else
		return *((*it).iptr);
}



// PRIVATE OPERATIONS
template <class symbol_info> ST<symbol_info> merge_or_fuse(const ST<symbol_info> &inner, const ST<symbol_info> &outer, bool merge_dups)
{
	ST<symbol_info> it;

	if (!outer.head)
	{
		it.head = inner.head;
	}
	else
	{
		ST_node<symbol_info> *to_add = inner.head;
		it.head = outer.head;
		while (to_add)
		{
			if (!merge_dups && it.check_for((*to_add).n))
				throw duplicate_symbol((*to_add).n);

			it.head = new ST_node<symbol_info>(it, (*to_add).n, (*to_add).iptr);
			to_add = (*to_add).rest.head;
		}
	}

	return it;
}


// check for "name", return ptr to its node or 0 if not there
template <class symbol_info> const ST_node<symbol_info> *ST<symbol_info>::check_for(const name_type &name) const
{
	if (head == 0)
		return 0;
	else if (Symbols_are_equal((*head).n, name))
		return head;
	else
		return (*head).rest.check_for(name);
}


// PRINTING

template <class symbol_info> string ST<symbol_info>::repr_method()
{
	String result = "ST(";
	ST_node<symbol_info> *h = this->head;
	while (h != 0) {
		result = result + repr(h->n) + "-->" + repr(*h->iptr);
		h = h->rest.head;
		if (h) result = result + ", ";
	}
	result = result + ")";
	return result;
}


template <class symbol_info> string ST<symbol_info>::str_just_names()
{
	string result = "ST{";
	HaverfordCS::list<string> namesInAlready;
	ST_node<symbol_info> *h = this->head;
	bool first = true;
	while (h != 0) {
		string nextName = str(h->n);
		if (! find(nextName, namesInAlready)) {
			namesInAlready = HaverfordCS::list<string>(nextName, namesInAlready);
			result = result + (first?"":", ") + repr(h->n);
			first = false;
		}
		h = h->rest.head;
	}
	result = result + "}";
	return result;
}
