/*
  fsm@robots.ox.ac.uk
*/
#ifdef __GNUC__
#pragma implementation
#endif
#include "osl_edgel_chain.h"

#include <vcl_cstdlib.h>
#include <vcl_iostream.h>
#include <vcl_iomanip.h>
#include <vcl_new.h>

#include <osl/osl_hacks.h>

//--------------------------------------------------------------------------------

osl_edgel_chain::osl_edgel_chain() : n(0), x(0), y(0), grad(0), theta(0) { }

osl_edgel_chain::osl_edgel_chain(int n_)
  : n(n_)
  , x(new float[n fsm_pad])
  , y(new float[n fsm_pad])
  , grad(new float[n fsm_pad])
  , theta(new float[n fsm_pad])
{ }

osl_edgel_chain::osl_edgel_chain(osl_edgel_chain const &that)
  : n(that.n)
  , x(new float[n fsm_pad])
  , y(new float[n fsm_pad])
  , grad(new float[n fsm_pad])
  , theta(new float[n fsm_pad])
{
  for (int i=0; i<n; ++i) {
    x[i] = that.x[i];
    y[i] = that.y[i];
    grad[i] = that.grad[i];
    theta[i] = that.theta[i];
  }
}
void osl_edgel_chain::operator=(osl_edgel_chain const &that) {
  vcl_cerr << __FILE__ ": assignment to osl_edgel_chain" << vcl_endl;
  if (this != &that) {
    this->~osl_edgel_chain();
    new (this) osl_edgel_chain(that);
  }
}

osl_edgel_chain::~osl_edgel_chain() {
  n = 0;
  fsm_delete_array x; x = 0;
  fsm_delete_array y; y = 0;
  fsm_delete_array grad; grad = 0;
  fsm_delete_array theta; theta = 0;
}

float  osl_edgel_chain::GetGrad(int i) const { return grad[i]; }
float *osl_edgel_chain::GetGrad() const { return grad; }
float  osl_edgel_chain::GetTheta(int i) const { return theta[i]; }
float *osl_edgel_chain::GetTheta() const { return theta; }
float  osl_edgel_chain::GetX(int i) const { return x[i]; }
float *osl_edgel_chain::GetX() const { return x; }
float  osl_edgel_chain::GetY(int i) const { return y[i]; }
float *osl_edgel_chain::GetY() const { return y; }
void osl_edgel_chain::SetGrad(float v, int i) { grad[i] = v; }
void osl_edgel_chain::SetTheta(float v, int i) { theta[i] = v; }
void osl_edgel_chain::SetX(float v, int i) { x[i] = v; }
void osl_edgel_chain::SetY(float v, int i) { y[i] = v; }
int osl_edgel_chain::size() const { return n; }

void osl_edgel_chain::SetLength(int nn) {
  if (nn <= n)
    n = nn;
  else
    vcl_abort();
}

void osl_edgel_chain::write_ascii(vcl_ostream &os) const {
  os << n << vcl_endl; // length
  for (int i=0; i<n; ++i)
    os << x[i] << ' ' << y[i] << ' ' << grad[i] << ' ' << theta[i] << vcl_endl;
}

void osl_edgel_chain::read_ascii(vcl_istream &is) {
  {
    int n_ = -1;
    is >> vcl_ws >> n_;
    if (n_<0 || is.bad()) {
      vcl_cerr << __FILE__ ": failed to read length of osl_edgel_chain" << vcl_endl;
      return;
    }
    //SetLength(n_);
    this->~osl_edgel_chain();       // destruct
    new (this) osl_edgel_chain(n_); // construct
  }

  for (int i=0; i<n; ++i)
    is >> vcl_ws >> x[i] >> y[i] >> grad[i] >> theta[i];
  if (is.bad()) {
    vcl_cerr << __FILE__ ": stream bad before end of osl_edgel_chain" << vcl_endl;
    return;
  }

  // if we get here, it's probably OK.
}

